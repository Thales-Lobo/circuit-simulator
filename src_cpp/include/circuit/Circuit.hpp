#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include "circuit/Mesh.hpp"
#include <Eigen/Dense>

class Circuit {
private:
    // Meshes in this circuit
    std::vector<Mesh*> meshes;  
    // Currents of the meshes
    std::vector<std::complex<double>> meshCurrents;

public:
    // Constructor
    Circuit();
    Circuit(std::vector<Mesh*> meshes);

    // Add a mesh to the circuit
    void addMesh(Mesh* mesh);  
    // Return a vector with all circuit meshes
    std::vector<Mesh*> getMeshes() const;
    // Return the currents of the meshes
    std::vector<std::complex<double>> getMeshCurrents() const;
    // Analyzes which current sources are in more than one mesh
    std::unordered_map<ACCurrentSource*, std::vector<int>> Circuit::mapCurrentSourcesToMeshes() const;
    // Solve for mesh currents using matrix method
    void solveMeshCurrents();  
};

#endif // CIRCUIT_HPP
