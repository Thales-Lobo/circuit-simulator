#include "circuit/Mesh.hpp"
#include <algorithm>

// Default constructor
Mesh::Mesh() 
    : sources(), loads() {}

// Constructor with initial sources and loads
Mesh::Mesh(std::vector<Source*> sources, std::vector<Load*> loads) 
    : sources(std::move(sources)), loads(std::move(loads)) {}

// Add a source to the mesh
void Mesh::addSource(Source* source) {
    sources.push_back(source);
}

// Add a load to the mesh
void Mesh::addLoad(Load* load) {
    loads.push_back(load);
}

// Calculate total voltage of the mesh
std::complex<double> Mesh::calculateMeshVoltage() const {
    std::complex<double> totalVoltage(0.0, 0.0);
    
    for (const auto& source : sources) {
        if (auto voltageSource = dynamic_cast<ACVoltageSource*>(source)) {
            totalVoltage += voltageSource->getValue();
        }
    }
    return totalVoltage;
}

// Calculate total impedance of the mesh
std::complex<double> Mesh::calculateMeshImpedance() const {
    std::complex<double> totalImpedance(0.0, 0.0);
    for (const auto& load : loads) {
        totalImpedance += load->getImpedance();
    }
    return totalImpedance;
}

// Return a vector with all mesh loads
std::vector<Load*> Mesh::getLoads() const {
    return loads;
}

// Return a vector with all mesh sources
std::vector<Source*> Mesh::getSources() const {
    return sources;
}

// Return a vector with all common loads between two meshes
std::vector<Load*> Mesh::commonLoads(const Mesh* otherMesh) const {
    std::vector<Load*> common;

    // Convert otherMesh->loads to an unordered_set for O(1) lookups
    std::unordered_set<Load*> otherLoadsSet(otherMesh->loads.begin(), otherMesh->loads.end());

    for (const auto& load : loads) {
        if (otherLoadsSet.find(load) != otherLoadsSet.end()) {
            common.push_back(load);
        }
    }

    return common;
}
