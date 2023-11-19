#include "circuit/Circuit.hpp"
#include <emscripten/bind.h>

// Interface functions for creating and destroying Circuit objects
extern "C" {
    Circuit* CreateCircuit() {
        return new Circuit();
    }

    Circuit* CreateCircuitWithMeshes(const std::vector<std::shared_ptr<Mesh>>& meshes) {
        return new Circuit(meshes);
    }

    void DestroyCircuit(Circuit* circuit) {
        delete circuit;
    }
}

// Emscripten binding
EMSCRIPTEN_BINDINGS(circuit_module) {
    emscripten::class_<Circuit>("Circuit")
        .constructor<>()
        .constructor<const std::vector<std::shared_ptr<Mesh>>&>()
        .function("addMesh", &Circuit::addMesh)
        .function("getMeshes", &Circuit::getMeshes)
        .function("getMeshCurrents", &Circuit::getMeshCurrents)
        .function("getImpedanceMatrix", &Circuit::getImpedanceMatrix)
        .function("getVoltageVector", &Circuit::getVoltageVector)
        .function("getCurrentVector", &Circuit::getCurrentVector)
        .function("solveMeshCurrents", &Circuit::solveMeshCurrents);
}
