#ifndef MESH_HPP
#define MESH_HPP

// Includes
#include <vector>
#include <algorithm>
#include "sources/AC/ACVoltageSource.hpp"
#include "sources/AC/ACCurrentSource.hpp"
#include "components/Component.hpp"

class Mesh {
private:
    // Components in this mesh
    std::vector<ACVoltageSource*> ACVoltageSources;
    std::vector<ACCurrentSource*> ACCurrentSources;
    std::vector<Component*> components;  
    
public:
    // Constructors
    Mesh();
    Mesh(std::vector<Source*> sources, std::vector<Component*> components);

    // Add a AC voltage source to the mesh
    void addACVoltageSource(ACVoltageSource* ACVoltageSource); 
    // Add a AC current source to the mesh
    void addACCurrentSource(ACCurrentSource* ACCurrentSource);
    // Add a component to the mesh
    void addComponent(Component* component);
    // Calculate total voltage of the mesh
    std::complex<double> calculateMeshVoltage();
    // Calculate total impedance of the mesh
    std::complex<double> calculateMeshImpedance(); 
    // Return a vector with all mesh components
    std::vector<Component*> getComponents();
    // Return a vector with all common components between two meshs
    std::vector<Component*> commonComponents(Mesh* otherMesh);
};

#endif // MESH_HPP
