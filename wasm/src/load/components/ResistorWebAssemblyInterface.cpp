#include "load/components/Resistor.hpp"
#include <emscripten/bind.h>

// Interface functions for creating and destroying Resistor objects
extern "C" {
    Resistor* CreateResistor(double resistanceValue, double angularFrequency) {
        return new Resistor(resistanceValue, angularFrequency);
    }

    void DestroyResistor(Resistor* resistor) {
        delete resistor;
    }
}

// Emscripten binding
EMSCRIPTEN_BINDINGS(resistor_module) {
    emscripten::class_<Resistor, emscripten::base<Component>>("Resistor")
        .constructor<double, double>()
        .function("getComponentValue", &Resistor::getComponentValue)
        .function("getAngularFrequency", &Resistor::getAngularFrequency)
        .function("setComponentValue", &Resistor::setComponentValue)
        .function("setAngularFrequency", &Resistor::setAngularFrequency)
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
