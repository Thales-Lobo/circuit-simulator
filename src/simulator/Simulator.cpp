#include "simulator/Simulator.hpp"

Simulator::Simulator(Circuit* circuit) : circuit(circuit) {
    // Precompute shared loads
    computeSharedLoads();
}

// List all shared loads on the circuit
void Simulator::computeSharedLoads() {
    std::unordered_map<Load*, size_t> loadCount;
    for (Mesh* mesh : circuit->getMeshes()) {
        for (Load* load : mesh->getLoads()) {
            loadCount[load]++;
            if (loadCount[load] == 2) {
                sharedLoads.insert(load);
            }
        }
    }
}

// Calculate the mesh currents and assign them to loads and voltage sources within the mesh
void Simulator::runSimulation() {
    // First, solve for the mesh currents using the circuit's method
    circuit->solveMeshCurrents();
    
    // Retrieve the calculated mesh currents and the meshes from the circuit
    const auto& meshCurrents = circuit->getMeshCurrents();
    const auto& meshes = circuit->getMeshes();

    // Iterate over each mesh to assign the current to loads and voltage sources
    for (size_t index = 0; index < meshes.size(); ++index) {
        Mesh* mesh = meshes[index];
        std::complex<double> meshCurrent = meshCurrents[index];

        // Assign the current to each load in the mesh
        for (Load* load : mesh->getLoads()) {
            if (sharedLoads.find(load) == sharedLoads.end()) {
                // If the load is not shared with another mesh, assign the mesh current directly
                load->setCurrent(meshCurrent);
            } else {
                // If the load is shared, calculate the net current through the load
                size_t otherMeshIndex = getOtherMeshIndex(load, index);
                std::complex<double> otherMeshCurrent = meshCurrents[otherMeshIndex];
                load->setCurrent(meshCurrent - otherMeshCurrent);
            }
        }

        // Assign the current to each voltage source in the mesh
        for (Source* source : mesh->getSources()) {
            // Check if the source is a voltage source
            if (auto voltageSource = dynamic_cast<VoltageSource*>(source)) {
                // Assign the mesh current to the voltage source
                voltageSource->setCurrent(meshCurrent);
            }
        }
    }
}


// Implement logic to check if a load is shared between two meshes
bool Simulator::isSharedLoad(Load* load) const {
    return sharedLoads.find(load) != sharedLoads.end();
}

// Implement the logic to obtain the index of the other mesh that shares this load
size_t Simulator::getOtherMeshIndex(Load* load, size_t currentMeshIndex) const {
    const auto& meshes = circuit->getMeshes();
    for (size_t index = 0; index < meshes.size(); ++index) {
        if (index != currentMeshIndex && isSharedLoad(load)) {
            return static_cast<size_t>(index);
        }
    }
    throw std::runtime_error("Other mesh not found for shared load!");
}
