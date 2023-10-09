#include "simulator/Simulator.hpp"

Simulator::Simulator(Circuit* circuit) : circuit(circuit) {
    // Precompute shared loads
    computeSharedLoads();
}

// List all shared loads on the circuit
void Simulator::computeSharedLoads() {
    for (Mesh* mesh : circuit->getMeshes()) {
        for (Load* load : mesh->getLoads()) {
            if (isSharedLoad(load)) {
                sharedLoads.insert(load);
            }
        }
    }
}

// Calculate the mesh currents
void Simulator::runSimulation() {
    circuit->solveMeshCurrents();
    std::vector<std::complex<double>> meshCurrents = circuit->getMeshCurrents();

    // Assign currents and voltages to loads
    int numMeshes = circuit->getMeshes().size();
    for (int index = 0; index < numMeshes; index++) {
        Mesh* mesh = circuit->getMeshes()[index];
        std::complex<double> meshCurrent = meshCurrents[index];

        for (Load* load : mesh->getLoads()) {
            // If the load is unique to this mesh
            if (sharedLoads.find(load) == sharedLoads.end()) {
                load->setCurrent(meshCurrent);
            } else {
                // If the load is shared with another mesh
                int otherMeshIndex = getOtherMeshIndex(load, index);
                std::complex<double> otherMeshCurrent = meshCurrents[otherMeshIndex];
                std::complex<double> loadCurrent = meshCurrent - otherMeshCurrent;

                load->setCurrent(loadCurrent);
            }
        }
    }
}

// Implement logic to check if a load is shared between two meshes
bool Simulator::isSharedLoad(Load* load) {
    int loadCounter = 0;
    for (Mesh* mesh : circuit->getMeshes()) {
        if (std::find(mesh->getLoads().begin(), mesh->getLoads().end(), load) != mesh->getLoads().end()) {
            loadCounter++;
            // A load can only be in a maximum of 2 meshes at the same time
            if (loadCounter == 2) {
                return true;
            }
        }
    }
    return false;
}

// Implement the logic to obtain the index of the other mesh that shares this load
int Simulator::getOtherMeshIndex(Load* load, int currentMeshIndex) {
    int index = 0;
    for (Mesh* mesh : circuit->getMeshes()) {
        if (index != currentMeshIndex && std::find(mesh->getLoads().begin(), mesh->getLoads().end(), load) != mesh->getLoads().end()) {
            return index;
        }
        index++;
    }

    throw std::runtime_error("Other mesh not found for shared load!");
}
