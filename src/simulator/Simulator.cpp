#include "simulator/Simulator.hpp"

Simulator::Simulator(Circuit* circuit) : circuit(circuit) {
    if (!circuit) {
        throw std::invalid_argument("Circuit pointer cannot be null.");
    }
    computeSharedLoads();
}

// List all shared loads on the circuit
void Simulator::computeSharedLoads() {
    std::unordered_map<std::shared_ptr<Load>, size_t> loadCount;
    for (const auto& mesh : circuit->getMeshes()) {
        for (const auto& load : mesh->getLoads()) {
            if (++loadCount[load] == 2) {
                sharedLoads.insert(load);
            }
        }
    }
}

// Main function to run the simulation and calculate mesh currents
void Simulator::runSimulation() {
    // Solve mesh currents using the circuit's method
    circuit->solveMeshCurrents();

    // Retrieve the calculated mesh currents and the meshes from the circuit
    const auto& meshCurrents = circuit->getMeshCurrents();
    const auto& meshPointers = circuit->getMeshes(); // meshPointers are raw pointers (Mesh*)

    // Iterate over each mesh to assign the current to loads and voltage sources
    for (size_t index = 0; index < meshPointers.size(); index++) {
        Mesh* mesh = meshPointers[index];
        auto meshCurrent = meshCurrents[index];

        // Assign current to each load in the mesh
        assignCurrentToLoads(mesh, meshCurrent, index);

        // Assign current to each voltage source in the mesh
        assignCurrentToVoltageSources(mesh, meshCurrent);
    }
}


void Simulator::assignCurrentToLoads(Mesh* mesh, const std::complex<double>& meshCurrent, size_t meshIndex) {
    // Iterates over all loads in the mesh to assign current
    for (auto& load : mesh->getLoads()) {
        auto current = determineLoadCurrent(load, meshCurrent, meshIndex);
        load->setCurrent(current);
    }
}

std::complex<double> Simulator::determineLoadCurrent(const std::shared_ptr<Load>& load, const std::complex<double>& meshCurrent, size_t meshIndex) {
    // Handles shared and non-shared loads differently
    if (sharedLoads.find(load) == sharedLoads.end()) {
        // Directly assigns mesh current to non-shared loads
        return meshCurrent;
    } else {
        // Calculates net current for shared loads
        size_t otherMeshIndex = getOtherMeshIndex(load, meshIndex);
        auto otherMeshCurrent = circuit->getMeshCurrents()[otherMeshIndex];
        return meshCurrent - otherMeshCurrent;
    }
}

void Simulator::assignCurrentToVoltageSources(Mesh* mesh, const std::complex<double>& meshCurrent) {
    // Iterate over all sources in the mesh to assign the calculated current
    for (auto& source : mesh->getSources()) {
        // Differentiate between AC and DC voltage sources and set current
        if (auto acVoltageSource = std::dynamic_pointer_cast<ACVoltageSource>(source)) {
            acVoltageSource->setCurrent(meshCurrent);
        } else if (auto dcVoltageSource = std::dynamic_pointer_cast<DCVoltageSource>(source)) {
            dcVoltageSource->setCurrent(meshCurrent);
        }
    }
}

// Check if a load is shared between two meshes
bool Simulator::isSharedLoad(const std::shared_ptr<Load>& load) const {
    return sharedLoads.find(load) != sharedLoads.end();
}

// Obtain the index of the other mesh that shares this load
size_t Simulator::getOtherMeshIndex(const std::shared_ptr<Load>& load, size_t currentMeshIndex) const {
    const auto& meshes = circuit->getMeshes();
    for (size_t index = 0; index < meshes.size(); ++index) {
        // Check if load is shared and not in the current mesh
        if (index != currentMeshIndex && isSharedLoad(load)) {
            return index;
        }
    }
    // Throw an error if the other mesh is not found
    throw std::runtime_error("Other mesh not found for shared load!");
}
