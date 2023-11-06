#include "circuit/Circuit.hpp"

// Constructor using member initializer list
Circuit::Circuit() : meshes({}) {}

Circuit::Circuit(std::vector<Mesh*> meshes) : meshes(std::move(meshes)) {}

// Add a mesh to the circuit
void Circuit::addMesh(Mesh* mesh) {
    this->meshes.emplace_back(mesh);  
}

// Getters
std::vector<Mesh*> Circuit::getMeshes() const {
    return this->meshes;
}

std::vector<std::complex<double>> Circuit::getMeshCurrents() const {
    return this->meshCurrents;
}

std::unordered_map<ACCurrentSource*, std::vector<int>> Circuit::mapCurrentSourcesToMeshes() const {
    std::unordered_map<ACCurrentSource*, std::vector<int>> sourceToMeshesMap;
    for (int i = 0; i < meshes.size(); i++) {
        for (const auto& source : meshes[i]->getSources()) {
            if (auto currentSource = dynamic_cast<ACCurrentSource*>(source)) {
                sourceToMeshesMap[currentSource].push_back(i);
            }
        }
    }
    return sourceToMeshesMap;
}

// Use linear algebra to calculate mesh currents
void Circuit::solveMeshCurrents() {
    int numMeshes = meshes.size();
    auto currentSourcesMap = mapCurrentSourcesToMeshes();
    int numCurrentSources = currentSourcesMap.size();
    int matrixSize = numMeshes + numCurrentSources;

    // Adjust the size of the matrix and vector to include current sources
    Eigen::MatrixXcd impedanceMatrix = Eigen::MatrixXcd::Zero(matrixSize, matrixSize);
    Eigen::VectorXcd voltageVector(matrixSize);

    // Fill matrices impedanceMatrix and B using KVL
    for (int row = 0; row < numMeshes; row++) {
        Mesh* mesh = meshes[row];
        std::unordered_set<Load*> meshLoads(mesh->getLoads().begin(), mesh->getLoads().end());

        // Handle voltage sources
        for (int column = 0; column < numMeshes; column++) {
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
    int rowIndex = numMeshes;
    for (const auto& [currentSource, meshIndices] : currentSourcesMap) {
        // Current source between two meshes
        if (meshIndices.size() == 2) { 
            impedanceMatrix(rowIndex, meshIndices[0]) = 1;
            impedanceMatrix(rowIndex, meshIndices[1]) = -1;
            voltageVector(rowIndex) = currentSource->getValue();
            rowIndex++;
        }
        // For the voltage of the current source
        impedanceMatrix(rowIndex, rowIndex) = 1;
        voltageVector(rowIndex) = 0;
        rowIndex++;
    }

    // Solve the system of equations
    Eigen::VectorXcd solutionVector = impedanceMatrix.colPivHouseholderQr().solve(voltageVector);

    // Update the meshCurrents field
    meshCurrents.assign(solutionVector.data(), solutionVector.data() + numMeshes);
}
