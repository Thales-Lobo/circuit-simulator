#include "circuit/Mesh.hpp"
#include <emscripten/bind.h>

// Interface functions for creating and destroying Mesh objects
extern "C" {
    Mesh* CreateMesh() {
        return new Mesh();
    }

    Mesh* CreateMeshWithComponents(const std::vector<std::shared_ptr<Source>>& sources, const std::vector<std::shared_ptr<Load>>& loads) {
        return new Mesh(sources, loads);
    }

    void DestroyMesh(Mesh* mesh) {
        delete mesh;
    }
}

// Emscripten binding
EMSCRIPTEN_BINDINGS(mesh_module) {
    emscripten::class_<Mesh>("Mesh")
        .constructor<>()
        .constructor<const std::vector<std::shared_ptr<Source>>&, const std::vector<std::shared_ptr<Load>>&>()
        .function("addSource", &Mesh::addSource)
        .function("addLoad", &Mesh::addLoad)
        .function("getSources", &Mesh::getSources)
        .function("getLoads", &Mesh::getLoads)
        .function("calculateMeshVoltage", &Mesh::calculateMeshVoltage)
        .function("calculateMeshImpedance", &Mesh::calculateMeshImpedance)
        .function("commonLoads", &Mesh::commonLoads);
}
