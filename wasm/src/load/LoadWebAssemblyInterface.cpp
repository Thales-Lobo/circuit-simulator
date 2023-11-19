#include "load/Load.hpp"
#include <emscripten/bind.h>

// Interface functions for creating and destroying Load objects
extern "C" {
    Load* CreateLoad(double firstValue, double secondValue, Load::RepresentationMode mode) {
        return new Load(firstValue, secondValue, mode);
    }

    void DestroyLoad(Load* load) {
        delete load;
    }
}

// Emscripten binding
EMSCRIPTEN_BINDINGS(load_module) {
    emscripten::class_<Load>("Load")
        .constructor<double, double, Load::RepresentationMode>()
        .function("getImpedance", &Load::getImpedance)
        .function("getVoltage", &Load::getVoltage)
        .function("getCurrent", &Load::getCurrent)
        .function("getComplexPower", &Load::getComplexPower)
        .function("getActivePower", &Load::getActivePower)
        .function("getReactivePower", &Load::getReactivePower)
        .function("getPhase", &Load::getPhase)
        .function("setCurrent", &Load::setCurrent);
}
