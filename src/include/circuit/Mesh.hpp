#ifndef MESH_HPP
#define MESH_HPP

// Includes
#include <vector>
#include <algorithm>
#include "sources/AC/ACVoltageSource.hpp"
#include "sources/AC/ACCurrentSource.hpp"
#include "load/Load.hpp"

class Mesh {
private:
    // Loads in this mesh
    std::vector<ACVoltageSource*> ACVoltageSources;
    std::vector<ACCurrentSource*> ACCurrentSources;
    std::vector<Load*> loads;  
    
public:
    // Constructors
    Mesh();
    Mesh(std::vector<Source*> sources, std::vector<Load*> loads);

    // Add a AC voltage source to the mesh
    void addACVoltageSource(ACVoltageSource* ACVoltageSource); 
    // Add a AC current source to the mesh
    void addACCurrentSource(ACCurrentSource* ACCurrentSource);
    // Add a load to the mesh
    void addLoad(Load* load);
    // Calculate total voltage of the mesh
    std::complex<double> calculateMeshVoltage();
    // Calculate total impedance of the mesh
    std::complex<double> calculateMeshImpedance(); 
    // Return a vector with all mesh loads
    std::vector<Load*> getLoads();
    // Return a vector with all common loads between two meshs
    std::vector<Load*> commonLoads(Mesh* otherMesh);
};

#endif // MESH_HPP
