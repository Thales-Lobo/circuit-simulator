#include "circuit/Circuit.hpp"
#include <Eigen/Dense>

// Constructor
Circuit::Circuit() {
    this->meshes = {};
}

Circuit::Circuit(std::vector<Mesh*> meshes) {
    this->meshes = meshes;
}

// Add a mesh to the circuit
void Circuit::addMesh(Mesh* mesh) {
    meshes.push_back(mesh);  
}

// Return a vector with all circuit meshes
std::vector<Mesh*> Circuit::getMeshes() {
    return this->meshes;
}

std::vector<std::complex<double>> Circuit::getMeshCurrents() const {
    return this->meshCurrents;
}

void Circuit::solveMeshCurrents() {
    int numMeshes = meshes.size();

    // Complex impedances matrix and voltage
    Eigen::MatrixXcd impedanceMatrix(numMeshes, numMeshes);
    Eigen::VectorXcd voltageVector(numMeshes);

    // Fill matrices impedanceMatrix and B using KVL
    for (int row = 0; row < numMeshes; row++) {
        Mesh* mesh = meshes[row];

        for (int column = 0; column < numMeshes; column++) {
            if (row == column) {
                // Main diagonal
                impedanceMatrix(row, column) = mesh->calculateMeshImpedance();  
            } else {
                std::vector<Component*> commonComponents    = mesh->commonComponents(meshes[column]);
                std::complex<double> totalCommonImpedance   = 0.0;

                for (Component* component : commonComponents) {
                    totalCommonImpedance += component->getImpedance();
                }

                impedanceMatrix(row, column) = -totalCommonImpedance;
            }
        }
        // Sum of source voltages in the mesh
        voltageVector(row) = mesh->calculateMeshVoltage();  
    }

    // Solve the system of equations
    Eigen::VectorXcd currentVector = impedanceMatrix.colPivHouseholderQr().solve(voltageVector);

    // Update the meshCurrents field
    meshCurrents.clear();
    for (int index = 0; index < numMeshes; index++) {
        meshCurrents.push_back(currentVector(index));
    }
}
