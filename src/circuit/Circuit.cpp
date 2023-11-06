#include "circuit/Circuit.hpp"
#include <iostream>

// Constructor using member initializer list
Circuit::Circuit() : meshes({}) {}

Circuit::Circuit(std::vector<Mesh*> meshes) : meshes(std::move(meshes)) {}

// Add a mesh to the circuit
void Circuit::addMesh(Mesh* mesh) {
    meshes.emplace_back(mesh);  
}

// Getters
std::vector<Mesh*> Circuit::getMeshes() const {
    return meshes;
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
std::unordered_map<CurrentSource*, std::vector<size_t>> Circuit::mapCurrentSourcesToMeshes() const {
    std::unordered_map<CurrentSource*, std::vector<size_t>> sourceToMeshesMap;
    for (size_t index = 0; index < meshes.size(); index++) {
        for (Source* source : meshes[index]->getSources()) {
            if (auto currentSource = dynamic_cast<CurrentSource*>(source)) {
                sourceToMeshesMap[currentSource].push_back(index);
            }
        }
    }
    return sourceToMeshesMap;
}

// Use linear algebra to calculate mesh currents
void Circuit::solveMeshCurrents() {
    size_t numMeshes            = meshes.size();
    auto currentSourcesMap      = mapCurrentSourcesToMeshes();
    size_t numCurrentSources    = currentSourcesMap.size();
    size_t matrixSize           = numMeshes + numCurrentSources;

    // Adjust the size of the matrix and vector to include current sources
    impedanceMatrix = Eigen::MatrixXcd::Zero(matrixSize, matrixSize);
    voltageVector = Eigen::VectorXcd::Zero(matrixSize);

    // Fill matrices impedanceMatrix and B using KVL
    for (size_t row = 0; row < numMeshes; row++) {
        Mesh* mesh = meshes[row];
        auto loads = mesh->getLoads();
        
        std::unordered_set<Load*> meshLoads(loads.begin(), loads.end());

        // Handle voltage sources
        for (size_t column = 0; column < numMeshes; column++) {
            if (row == column) {
                impedanceMatrix(row, column) = mesh->calculateMeshImpedance();  
            } else {
                std::complex<double> totalCommonImpedance = 0.0;
                
                for (Load* load : meshes[column]->getLoads()) {
                    if (meshLoads.find(load) != meshLoads.end()) {
                        totalCommonImpedance += load->getImpedance();
                    }
                }
                impedanceMatrix(row, column) = -totalCommonImpedance;
            }
        }
        voltageVector(row) = mesh->calculateMeshVoltage();  
    }

    // Handle current sources
    size_t extraRow = numMeshes;
    for (const auto& [currentSource, meshIndices] : currentSourcesMap) {
        // Current source between two meshes
        if (meshIndices.size() == 2) { 
            impedanceMatrix(extraRow, meshIndices[0]) = 1;
            impedanceMatrix(extraRow, meshIndices[1]) = -1;
            impedanceMatrix(meshIndices[0], extraRow) = -1;
            impedanceMatrix(meshIndices[1], extraRow) = 1;
            voltageVector(extraRow) = currentSource->getCurrent();
            extraRow++;
        }
        // For the voltage of the current source
        impedanceMatrix(extraRow, extraRow) = 1;
        voltageVector(extraRow) = 0;
        extraRow++;
    }
    // Solve the system of equations
    Eigen::ColPivHouseholderQR<Eigen::MatrixXcd> solver = impedanceMatrix.colPivHouseholderQr();
    currentVector = solver.solve(voltageVector);

    // Check if the solution is valid
    if (solver.info() != Eigen::Success) {
        throw std::runtime_error("Failed to solve the mesh currents.");
    }

    // Update the meshCurrents field
    meshCurrents.assign(currentVector.data(), currentVector.data() + numMeshes);

    // Assign the calculated voltages to the respective current sources
    for (size_t extraindex = numMeshes; extraindex < static_cast<size_t>(currentVector.size()); ++extraindex) {
        auto it = std::next(currentSourcesMap.begin(), extraindex - numMeshes);
        CurrentSource* currentSource = static_cast<CurrentSource*>(it->first);
        currentSource->setVoltage(currentVector[extraindex]);
    }
}
