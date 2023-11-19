#include "load/components/Component.hpp"
#include <emscripten/bind.h>

// Interface functions for creating and destroying Component objects
extern "C" {
    Component* CreateComponent(double componentValue, double angularFrequency) {
        return new Component(componentValue, angularFrequency);
    }

    void DestroyComponent(Component* component) {
        delete component;
    }
}

// Emscripten binding
EMSCRIPTEN_BINDINGS(component_module) {
    emscripten::class_<Component>("Component")
        .constructor<double, double>()
        .function("getComponentValue", &Component::getComponentValue)
        .function("getAngularFrequency", &Component::getAngularFrequency)
        .function("setComponentValue", &Component::setComponentValue)
        .function("setAngularFrequency", &Component::setAngularFrequency)
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
