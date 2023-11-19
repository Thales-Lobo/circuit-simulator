#include "circuit/Mesh.hpp"

// Default constructor
Mesh::Mesh() 
    : sources(), loads() {}

// Constructor with initial sources and loads
Mesh::Mesh(std::vector<std::shared_ptr<Source>> sources, std::vector<std::shared_ptr<Load>> loads) 
    : sources(sources), loads(loads) {}

// Return a vector with all mesh loads
std::vector<std::shared_ptr<Load>> Mesh::getLoads() const {
    return loads;
}

// Return a vector with all mesh sources
std::vector<std::shared_ptr<Source>> Mesh::getSources() const {
    return sources;
}

// Add a source to the mesh
void Mesh::addSource(std::shared_ptr<Source> source) {
    sources.push_back(source);
}

// Add a load to the mesh
void Mesh::addLoad(std::shared_ptr<Load> load) {
    loads.push_back(load);
}

std::complex<double> Mesh::calculateMeshVoltage() const {
    std::complex<double> totalVoltage(0.0, 0.0);

    for (const auto& sourcePtr : sources) {
        // Dynamic cast to check and convert to ACVoltageSource
        if (auto voltageSource = std::dynamic_pointer_cast<ACVoltageSource>(sourcePtr)) {
            totalVoltage += voltageSource->getVoltage();
        }
        // Dynamic cast to check and convert to DCVoltageSource
        else if (auto voltageSource = std::dynamic_pointer_cast<DCVoltageSource>(sourcePtr)) {
            totalVoltage += voltageSource->getVoltage();
        }
    }

    return totalVoltage;
}

// Calculate total impedance of the mesh
std::complex<double> Mesh::calculateMeshImpedance() const {
    std::complex<double> totalImpedance(0.0, 0.0);
    
    for (const auto& loadPtr : loads) {
        totalImpedance += loadPtr->getImpedance();
    }

    // Include the internal impedance of voltage sources
    for (const auto& sourcePtr : sources) {
        // Check for AC voltage source
        if (auto voltageSource = std::dynamic_pointer_cast<ACVoltageSource>(sourcePtr)) {
            totalImpedance += voltageSource->getInternalLoad();
        }
        // Check for DC voltage source
        else if (auto voltageSource = std::dynamic_pointer_cast<DCVoltageSource>(sourcePtr)) {
            totalImpedance += voltageSource->getInternalLoad();
        }
    }

    return totalImpedance;
}

// Return a vector with all common loads between two meshes
std::vector<std::shared_ptr<Load>> Mesh::commonLoads(const std::shared_ptr<Mesh>& otherMesh) const {
    std::vector<std::shared_ptr<Load>> commonLoads;

    // Creating an unordered_set of shared_ptr from otherMesh's loads for efficient lookup
    std::unordered_set<std::shared_ptr<Load>> otherLoadsSet(otherMesh->loads.begin(), otherMesh->loads.end());
    
    for (const auto& loadPtr : loads) {
        if (otherLoadsSet.find(loadPtr) != otherLoadsSet.end()) {
            commonLoads.push_back(loadPtr);
        }
    }

    return commonLoads;
}
