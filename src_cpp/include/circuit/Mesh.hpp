#ifndef MESH_HPP
#define MESH_HPP

// Includes
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "sources/DC/DCVoltageSource.hpp"
#include "sources/DC/DCCurrentSource.hpp"
#include "sources/AC/ACVoltageSource.hpp"
#include "sources/AC/ACCurrentSource.hpp"
#include "load/Load.hpp"

class Mesh {
private:
    // Loads in this mesh
    std::vector<Source*> sources;
    std::vector<Load*> loads;  
    
public:
    // Constructors
    Mesh();
    Mesh(std::vector<Source*> sources, std::vector<Load*> loads);

    // Add a source to the mesh
    void Mesh::addSource(Source* source);
    // Add a load to the mesh
    void addLoad(Load* load);
    // Calculate total voltage of the mesh
    std::complex<double> calculateMeshVoltage() const;
    // Calculate total impedance of the mesh
    std::complex<double> calculateMeshImpedance() const; 
    // Return a vector with all mesh loads
    std::vector<Load*> getLoads() const;
    // Return a vector with all mesh sources
    std::vector<Source*> Mesh::getSources() const;
    // Return a vector with all common loads between two meshs
    std::vector<Load*> commonLoads(const Mesh* otherMesh) const;
};

#endif // MESH_HPP
