#include "circuit/Circuit.hpp"
#include <iostream>

// Constructor using member initializer list
Circuit::Circuit() {}

Circuit::Circuit(std::vector<std::shared_ptr<Mesh>> initMeshes)
    : meshes(initMeshes) {}

// Add a mesh to the circuit
void Circuit::addMesh(std::shared_ptr<Mesh> mesh) {
    meshes.push_back(mesh);  
}

// Getters
std::vector<Mesh*> Circuit::getMeshes() const {
    std::vector<Mesh*> meshPointers;
    for (const auto& mesh : meshes) {
        meshPointers.push_back(mesh.get());
    }
    return meshPointers;
}

std::vector<std::complex<double>> Circuit::getMeshCurrents() const {
    return meshCurrents;
}

const Eigen::MatrixXcd& Circuit::getImpedanceMatrix() const {
    return impedanceMatrix;
}

const Eigen::VectorXcd& Circuit::getVoltageVector() const {
    return voltageVector;
}

const Eigen::VectorXcd& Circuit::getCurrentVector() const {
    return currentVector;
}

// Define a function to map current sources to the meshes they belong to
Circuit::CurrentSourceMaps Circuit::mapCurrentSourcesToMeshes() const {
    CurrentSourceMaps maps;

    for (size_t index = 0; index < meshes.size(); ++index) {
        for (const auto& source : meshes[index]->getSources()) {
            auto acSource = std::dynamic_pointer_cast<ACCurrentSource>(source);
            if (acSource) {
                maps.acSources[acSource.get()].push_back(index);
            }
            else {
                auto dcSource = std::dynamic_pointer_cast<DCCurrentSource>(source);
                if (dcSource) {
                    maps.dcSources[dcSource.get()].push_back(index);
                }
            }
        }
    }

    return maps;
}

// Use linear algebra to calculate mesh currents
void Circuit::solveMeshCurrents() {
    auto currentSourcesMaps = mapCurrentSourcesToMeshes();
    size_t numMeshes = meshes.size();
    
    // Calculate the total number of AC and DC current sources
    size_t numACCurrentSources  = currentSourcesMaps.acSources.size();
    size_t numDCCurrentSources  = currentSourcesMaps.dcSources.size();
    size_t numCurrentSources    = numACCurrentSources + numDCCurrentSources;
    size_t matrixSize           = numMeshes + numCurrentSources;

    // Prepare and solve the vectors and matrices of the system of equations
    prepareImpedanceMatrix(numMeshes, matrixSize, currentSourcesMaps);
    prepareVoltageVector(numMeshes, matrixSize);
    solveSystemOfEquations();

    assignCurrentsToSources(numMeshes, currentSourcesMaps);
}

// Prepares the impedance matrix by filling in the values for each mesh and handling current sources
void Circuit::prepareImpedanceMatrix(size_t numMeshes, size_t matrixSize, const CurrentSourceMaps& currentSourcesMaps) {
    impedanceMatrix = Eigen::MatrixXcd::Zero(matrixSize, matrixSize);

    for (size_t row = 0; row < numMeshes; row++) {
        fillImpedanceMatrixRow(row, meshes[row].get());
    }
    addCurrentSourcesToImpedanceMatrix(numMeshes, currentSourcesMaps);
}

// Fills a single row of the impedance matrix based on the mesh's impedance and common impedances with other meshes
void Circuit::fillImpedanceMatrixRow(size_t row, const Mesh* mesh) {
    for (size_t column = 0; column < meshes.size(); column++) {
        if (row == column) {
            impedanceMatrix(row, column) = mesh->calculateMeshImpedance();  
        } else {
            std::complex<double> commonImpedance = calculateCommonImpedance(mesh, meshes[column].get());
            impedanceMatrix(row, column) = -commonImpedance;
        }
    }
}

// Returns the total impedance value between 2 meshes
std::complex<double> Circuit::calculateCommonImpedance(const Mesh* mesh1, const Mesh* mesh2) const {
    std::complex<double> totalCommonImpedance = 0.0;
    auto mesh1Loads = mesh1->getLoads();
    auto mesh2Loads = mesh2->getLoads();

    std::unordered_set<std::shared_ptr<Load>> mesh1LoadsSet(mesh1Loads.begin(), mesh1Loads.end());

    for (const auto& load : mesh2Loads) {
        if (mesh1LoadsSet.find(load) != mesh1LoadsSet.end()) {
            totalCommonImpedance += load->getImpedance();
        }
    }

    return totalCommonImpedance;
}

// Adds the effects of current sources into the impedance matrix
void Circuit::addCurrentSourcesToImpedanceMatrix(size_t numMeshes, const CurrentSourceMaps& currentSourcesMaps) {
    size_t extraRow = numMeshes;

    // Iterate through AC current sources
    for (const auto& [acCurrentSource, meshIndices] : currentSourcesMaps.acSources) {
        // Handle current sources between two meshes
        if (meshIndices.size() == 2) { 
            addCurrentSourceBetweenMeshes(extraRow, meshIndices);
            extraRow++;
        }
        // Set a placeholder for the voltage of the current source
        impedanceMatrix(extraRow, extraRow) = 1;
        extraRow++;
    }

    // Iterate through DC current sources
    for (const auto& [dcCurrentSource, meshIndices] : currentSourcesMaps.dcSources) {
        // Handle current sources between two meshes
        if (meshIndices.size() == 2) { 
            addCurrentSourceBetweenMeshes(extraRow, meshIndices);
            extraRow++;
        }
        // Set a placeholder for the voltage of the current source
        impedanceMatrix(extraRow, extraRow) = 1;
        extraRow++;
    }
}

// Adds the effect of a current source that is between two meshes into the impedance matrix
void Circuit::addCurrentSourceBetweenMeshes(size_t row, const std::vector<size_t>& meshIndices) {
    impedanceMatrix(row, meshIndices[0]) = 1;
    impedanceMatrix(row, meshIndices[1]) = -1;
    impedanceMatrix(meshIndices[0], row) = -1;
    impedanceMatrix(meshIndices[1], row) = 1;
}

// Prepares the voltage vector by setting the net voltage for each mesh and handling current sources.
void Circuit::prepareVoltageVector(size_t numMeshes, size_t matrixSize) {
    voltageVector = Eigen::VectorXcd::Zero(matrixSize);
    for (size_t index = 0; index < numMeshes; ++index) {
        voltageVector(index) = meshes[index]->calculateMeshVoltage();
    }
}

// Solves the system of equations to find the mesh currents
void Circuit::solveSystemOfEquations() {
    // Initialize the solver with the impedance matrix.
    Eigen::ColPivHouseholderQR<Eigen::MatrixXcd> solver(impedanceMatrix);

    // Check if the matrix decomposition is successful.
    if (solver.info() != Eigen::Success) {
        throw std::runtime_error("Matrix decomposition failed.");
    }

    // Solve the system of equations.
    currentVector = solver.solve(voltageVector);

    // Check if the equation solving process is successful.
    if (solver.info() != Eigen::Success) {
        throw std::runtime_error("Solving system of equations failed.");
    }

    // Ensure meshCurrents has the correct size.
    meshCurrents.resize(currentVector.size());

    // Assign the values from currentVector to meshCurrents using parentheses for access.
    for (Eigen::Index index = 0; index < currentVector.size(); ++index) {
        meshCurrents[index] = currentVector(index);
    }
}

// Assigns the calculated currents to the respective sources in the circuit.
void Circuit::assignCurrentsToSources(size_t numMeshes, const CurrentSourceMaps& currentSourcesMaps) {
    // Helper lambda to assign current to a source
    auto assignCurrent = [this, numMeshes](auto* source, const std::vector<size_t>& indices) {
        if (indices.size() == 1) {
            source->setVoltage(currentVector(numMeshes + indices.front()));
        } else if (indices.size() == 2) {
            auto voltageDifference = currentVector(numMeshes + indices.front()) - currentVector(numMeshes + indices.back());
            source->setVoltage(voltageDifference);
        }
    };

    // Iterate through AC current sources
    for (const auto& [source, indices] : currentSourcesMaps.acSources) {
        assignCurrent(source, indices);
    }

    // Iterate through DC current sources
    for (const auto& [source, indices] : currentSourcesMaps.dcSources) {
        assignCurrent(source, indices);
    }
}
