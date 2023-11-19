#include "load/components/Inductor.hpp"
#include <emscripten/bind.h>

// Interface functions for creating and destroying Inductor objects
extern "C" {
    Inductor* CreateInductor(double inductanceValue, double angularFrequency) {
        return new Inductor(inductanceValue, angularFrequency);
    }

    void DestroyInductor(Inductor* inductor) {
        delete inductor;
    }
}

// Emscripten binding
EMSCRIPTEN_BINDINGS(inductor_module) {
    emscripten::class_<Inductor, emscripten::base<Component>>("Inductor")
        .constructor<double, double>()
        .function("getComponentValue", &Inductor::getComponentValue)
        .function("getAngularFrequency", &Inductor::getAngularFrequency)
        .function("setComponentValue", &Inductor::setComponentValue)
        .function("setAngularFrequency", &Inductor::setAngularFrequency)
        // Inherited functions from Load
        .function("getImpedance", &Load::getImpedance)
        .function("getVoltage", &Load::getVoltage)
        .function("getCurrent", &Load::getCurrent)
        .function("getComplexPower", &Load::getComplexPower)
        .function("getActivePower", &Load::getActivePower)
        .function("getReactivePower", &Load::getReactivePower)
        .function("getPhase", &Load::getPhase)
        .function("setCurrent", &Load::setCurrent);
}
