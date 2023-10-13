#include "simulator/Simulator.hpp"

Simulator::Simulator(Circuit* circuit) : circuit(circuit) {
    // Precompute shared loads
    computeSharedLoads();
}

// List all shared loads on the circuit
void Simulator::computeSharedLoads() {
    std::unordered_map<Load*, int> loadCount;
    for (Mesh* mesh : circuit->getMeshes()) {
        for (Load* load : mesh->getLoads()) {
            loadCount[load]++;
            if (loadCount[load] == 2) {
                sharedLoads.insert(load);
            }
        }
    }
}

// Calculate the mesh currents
void Simulator::runSimulation() {
    circuit->solveMeshCurrents();
    const auto& meshCurrents = circuit->getMeshCurrents();
    const auto& meshes = circuit->getMeshes();

    for (size_t index = 0; index < meshes.size(); ++index) {
        Mesh* mesh = meshes[index];
        std::complex<double> meshCurrent = meshCurrents[index];

        for (Load* load : mesh->getLoads()) {
            if (sharedLoads.find(load) == sharedLoads.end()) {
                load->setCurrent(meshCurrent);
            } else {
                int otherMeshIndex = getOtherMeshIndex(load, index);
                std::complex<double> otherMeshCurrent = meshCurrents[otherMeshIndex];
                load->setCurrent(meshCurrent - otherMeshCurrent);
            }
        }
    }
}

// Implement logic to check if a load is shared between two meshes
bool Simulator::isSharedLoad(Load* load) const {
    return sharedLoads.find(load) != sharedLoads.end();
}

// Implement the logic to obtain the index of the other mesh that shares this load
int Simulator::getOtherMeshIndex(Load* load, int currentMeshIndex) const {
    const auto& meshes = circuit->getMeshes();
    for (size_t index = 0; index < meshes.size(); ++index) {
        if (index != currentMeshIndex && isSharedLoad(load)) {
            return static_cast<int>(index);
        }
    }
    throw std::runtime_error("Other mesh not found for shared load!");
}
