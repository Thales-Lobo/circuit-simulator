#include "simulator/Simulator.hpp"

Simulator::Simulator(Circuit* circuit) : circuit(circuit) {
    // Precompute shared components
    computeSharedComponents();
}

// List all shared components on the circuit
void Simulator::computeSharedComponents() {
    for (Mesh* mesh : circuit->getMeshes()) {
        for (Component* component : mesh->getComponents()) {
            if (isSharedComponent(component)) {
                sharedComponents.insert(component);
            }
        }
    }
}

// Calculate the mesh currents
void Simulator::runSimulation() {
    circuit->solveMeshCurrents();
    std::vector<std::complex<double>> meshCurrents = circuit->getMeshCurrents();

    // Assign currents and voltages to components
    int numMeshes = circuit->getMeshes().size();
    for (int index = 0; index < numMeshes; index++) {
        Mesh* mesh = circuit->getMeshes()[index];
        std::complex<double> meshCurrent = meshCurrents[index];

        for (Component* component : mesh->getComponents()) {
            // If the component is unique to this mesh
            if (sharedComponents.find(component) == sharedComponents.end()) {
                component->setCurrent(meshCurrent);
            } else {
                // If the component is shared with another mesh
                int otherMeshIndex = getOtherMeshIndex(component, index);
                std::complex<double> otherMeshCurrent = meshCurrents[otherMeshIndex];
                std::complex<double> componentCurrent = meshCurrent - otherMeshCurrent;

                component->setCurrent(componentCurrent);
            }
        }
    }
}

// Implement logic to check if a component is shared between two meshes
bool Simulator::isSharedComponent(Component* component) {
    int componentCounter = 0;
    for (Mesh* mesh : circuit->getMeshes()) {
        if (std::find(mesh->getComponents().begin(), mesh->getComponents().end(), component) != mesh->getComponents().end()) {
            componentCounter++;
            // A component can only be in a maximum of 2 meshes at the same time
            if (componentCounter == 2) {
                return true;
            }
        }
    }
    return false;
}

// Implement the logic to obtain the index of the other mesh that shares this component
int Simulator::getOtherMeshIndex(Component* component, int currentMeshIndex) {
    int index = 0;
    for (Mesh* mesh : circuit->getMeshes()) {
        if (index != currentMeshIndex && std::find(mesh->getComponents().begin(), mesh->getComponents().end(), component) != mesh->getComponents().end()) {
            return index;
        }
        index++;
    }

    throw std::runtime_error("Other mesh not found for shared component.");
}
