#include "circuit/Mesh.hpp"

// Constructor implementation
Mesh::Mesh() {
    this->ACVoltageSources  = {};
    this->ACCurrentSources  = {};
    this->loads        = {};
}

// Constructor with initial sources and loads
Mesh::Mesh(std::vector<Source*> sources, std::vector<Load*> loads) {
    for (Source* source : sources) {
        // Checking the font type and adding to the corresponding list
        if (dynamic_cast<ACVoltageSource*>(source)) {
            this->ACVoltageSources.push_back(dynamic_cast<ACVoltageSource*>(source));
        } else if (dynamic_cast<ACCurrentSource*>(source)) {
            this->ACCurrentSources.push_back(dynamic_cast<ACCurrentSource*>(source));
        }
    }
    this->loads = loads;
}

// Add a AC voltage source to the mesh
void Mesh::addACVoltageSource(ACVoltageSource* ACVoltageSource) {
    this->ACVoltageSources.push_back(ACVoltageSource);
}

// Add a AC current source to the mesh
void Mesh::addACCurrentSource(ACCurrentSource* ACCurrentSource) {
    this->ACCurrentSources.push_back(ACCurrentSource);
}

// Add a load to the mesh
void Mesh::addLoad(Load* load) {
    this->loads.push_back(load);
}

// Calculate total voltage of the mesh
std::complex<double> Mesh::calculateMeshVoltage() {
    std::complex<double> totalACVoltage(0.0, 0.0);

    for (ACVoltageSource* ACVoltageSource : this->ACVoltageSources) {
        totalACVoltage += ACVoltageSource->getValue();
    }

    return totalACVoltage;
}

// Calculate total impedance of the mesh
std::complex<double> Mesh::calculateMeshImpedance() {
    std::complex<double> totalImpedance(0.0, 0.0);
    for (Load* load : this->loads) {
        totalImpedance += load->getImpedance();
    }
    return totalImpedance;
}

// Return a vector with all mesh loads
std::vector<Load*> Mesh::getLoads() {
    return this->loads;
}

// Return a vector with all common loads between two meshs
std::vector<Load*> Mesh::commonLoads(Mesh* otherMesh) {
    std::vector<Load*> commonLoads;

    for (Load* load : this->loads) {
        if (std::find(otherMesh->loads.begin(), otherMesh->loads.end(), load) != otherMesh->loads.end()) {
            commonLoads.push_back(load);
        }
    }

    return commonLoads;
}
