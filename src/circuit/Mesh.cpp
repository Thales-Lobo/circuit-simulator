#include "circuit/Mesh.hpp"

// Default constructor
Mesh::Mesh() 
    : sources(), loads() {}

// Constructor with initial sources and loads
Mesh::Mesh(std::vector<Source*> sources, std::vector<Load*> loads) 
    : sources(std::move(sources)), loads(std::move(loads)) {}

// Return a vector with all mesh loads
std::vector<Load*> Mesh::getLoads() const {
    return loads;
}

// Return a vector with all mesh sources
std::vector<Source*> Mesh::getSources() const {
    return sources;
}

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
        if (auto voltageSource = dynamic_cast<VoltageSource*>(source)) {
            totalVoltage += voltageSource->getVoltage();
        }
    }
    return totalVoltage;
}

// Calculate total impedance of the mesh
std::complex<double> Mesh::calculateMeshImpedance() const {
    // total impedance from loads
    std::complex<double> totalImpedance(0.0, 0.0);
    for (const auto& load : loads) {
        totalImpedance += load->getImpedance();
    }
    // Include the internal impedance of voltage sources
    for (const auto& source : sources) {
        if (auto voltageSource = dynamic_cast<VoltageSource*>(source)) {
            totalImpedance += voltageSource->getInternalLoad();
        }
    }
    return totalImpedance;
}

// Return a vector with all common loads between two meshes
std::vector<Load*> Mesh::commonLoads(const Mesh* otherMesh) const {
    std::vector<Load*> commonLoads;

    // Convert otherMesh->loads to an unordered_set for O(1) lookups
    std::unordered_set<Load*> otherLoadsSet(otherMesh->loads.begin(), otherMesh->loads.end());

    for (const auto& load : loads) {
        if (otherLoadsSet.find(load) != otherLoadsSet.end()) {
            commonLoads.push_back(load);
        }
    }
    return commonLoads;
}
