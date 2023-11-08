#include "circuit/Circuit.hpp"
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <memory>

using CurrentSourceMap = std::unordered_map<CurrentSource*, std::vector<size_t>>;

// Constructor using member initializer list
Circuit::Circuit() : meshes({}) {}

Circuit::Circuit(std::vector<std::unique_ptr<Mesh>> initMeshes)
    : meshes(std::move(initMeshes)) {}

// Add a mesh to the circuit
void Circuit::addMesh(std::unique_ptr<Mesh> mesh) {
    meshes.push_back(std::move(mesh));  
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
CurrentSourceMap Circuit::mapCurrentSourcesToMeshes() const {
    CurrentSourceMap sourceToMeshesMap;
    for (size_t index = 0; index < meshes.size(); ++index) {
        for (const auto& source : meshes[index]->getSources()) {
            if (auto* currentSource = dynamic_cast<CurrentSource*>(source)) {
                sourceToMeshesMap[currentSource].push_back(index);
            }
        }
    }
    return sourceToMeshesMap;
}

// Use linear algebra to calculate mesh currents
void Circuit::solveMeshCurrents() {
    auto currentSourcesMap = mapCurrentSourcesToMeshes();
    size_t numMeshes = meshes.size();
    size_t numCurrentSources = currentSourcesMap.size();
    size_t matrixSize = numMeshes + numCurrentSources;

    prepareImpedanceMatrix(numMeshes, matrixSize, currentSourcesMap);
    prepareVoltageVector(numMeshes, matrixSize);

    solveSystemOfEquations();

    assignCurrentsToSources(numMeshes, currentSourcesMap);
}

// Prepares the impedance matrix by filling in the values for each mesh and handling current sources
void Circuit::prepareImpedanceMatrix(size_t numMeshes, size_t matrixSize, const CurrentSourceMap& currentSourcesMap) {
    impedanceMatrix = Eigen::MatrixXcd::Zero(matrixSize, matrixSize);

    for (size_t row = 0; row < numMeshes; ++row) {
        fillImpedanceMatrixRow(row, meshes[row].get());
    }

    addCurrentSourcesToImpedanceMatrix(numMeshes, currentSourcesMap);
}

// Fills a single row of the impedance matrix based on the mesh's impedance and common impedances with other meshes
void Circuit::fillImpedanceMatrixRow(size_t row, const Mesh* mesh) {
    for (size_t column = 0; column < meshes.size(); ++column) {
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

    std::unordered_set<Load*> mesh1LoadsSet(mesh1Loads.begin(), mesh1Loads.end());

    for (const auto& load : mesh2Loads) {
        if (mesh1LoadsSet.find(load) != mesh1LoadsSet.end()) {
            totalCommonImpedance += load->getImpedance();
        }
    }

    return totalCommonImpedance;
}

// Adds the effects of current sources into the impedance matrix
void Circuit::addCurrentSourcesToImpedanceMatrix(size_t numMeshes, const CurrentSourceMap& currentSourcesMap) {
    size_t extraRow = numMeshes;
    for (const auto& [currentSource, meshIndices] : currentSourcesMap) {
        // Handle current sources between two meshes
        if (meshIndices.size() == 2) { 
            addCurrentSourceBetweenMeshes(extraRow, meshIndices);
            extraRow++;
        }
        // Placeholder for the voltage of the current source
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

// Solves the system of equations to find the mesh currents.
void Circuit::solveSystemOfEquations() {
    Eigen::ColPivHouseholderQR<Eigen::MatrixXcd> solver(impedanceMatrix);
    if (solver.info() != Eigen::Success) {
        throw std::runtime_error("Matrix decomposition failed.");
    }
    currentVector = solver.solve(voltageVector);
    if (solver.info() != Eigen::Success) {
        throw std::runtime_error("Solving system of equations failed.");
    }
}

// Assigns the calculated currents to the respective sources in the circuit.
void Circuit::assignCurrentsToSources(size_t numMeshes, const CurrentSourceMap& currentSourcesMap) {
    for (const auto& [source, indices] : currentSourcesMap) {
        if (indices.size() == 1) {
            source->setVoltage(currentVector(numMeshes + indices.front()));
        } else if (indices.size() == 2) {
            // Assuming the current source is between two meshes, assign the voltage accordingly
            auto voltageDifference = currentVector(numMeshes + indices.front()) - currentVector(numMeshes + indices.back());
            source->setVoltage(voltageDifference);
        }
    }
}
