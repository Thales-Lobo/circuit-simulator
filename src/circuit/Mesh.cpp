#include "circuit/Mesh.hpp"

// Constructor implementation
Mesh::Mesh() {
    this->ACVoltageSources  = {};
    this->ACCurrentSources  = {};
    this->components        = {};
}

// Constructor with initial sources and components
Mesh::Mesh(std::vector<Source*> sources, std::vector<Component*> components) {
    for (Source* source : sources) {
        // Checking the font type and adding to the corresponding list
        if (dynamic_cast<ACVoltageSource*>(source)) {
            this->ACVoltageSources.push_back(dynamic_cast<ACVoltageSource*>(source));
        } else if (dynamic_cast<ACCurrentSource*>(source)) {
            this->ACCurrentSources.push_back(dynamic_cast<ACCurrentSource*>(source));
        }
    }
    this->components = components;
}

// Add a AC voltage source to the mesh
void Mesh::addACVoltageSource(ACVoltageSource* ACVoltageSource) {
    this->ACVoltageSources.push_back(ACVoltageSource);
}

// Add a AC current source to the mesh
void Mesh::addACCurrentSource(ACCurrentSource* ACCurrentSource) {
    this->ACCurrentSources.push_back(ACCurrentSource);
}

// Add a component to the mesh
void Mesh::addComponent(Component* component) {
    this->components.push_back(component);
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
    for (Component* component : this->components) {
        totalImpedance += component->getImpedance();
    }
    return totalImpedance;
}

// Return a vector with all mesh components
std::vector<Component*> Mesh::getComponents() {
    return this->components;
}

// Return a vector with all common components between two meshs
std::vector<Component*> Mesh::commonComponents(Mesh* otherMesh) {
    std::vector<Component*> commonComponents;

    for (Component* component : this->components) {
        if (std::find(otherMesh->components.begin(), otherMesh->components.end(), component) != otherMesh->components.end()) {
            commonComponents.push_back(component);
        }
    }

    return commonComponents;
}
