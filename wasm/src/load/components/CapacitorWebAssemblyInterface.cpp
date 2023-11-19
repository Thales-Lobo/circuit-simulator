#include "load/components/Capacitor.hpp"
#include <emscripten/bind.h>

// Interface functions for creating and destroying Capacitor objects
extern "C" {
    Capacitor* CreateCapacitor(double capacitanceValue, double angularFrequency) {
        return new Capacitor(capacitanceValue, angularFrequency);
    }

    void DestroyCapacitor(Capacitor* capacitor) {
        delete capacitor;
    }
}

// Emscripten binding
EMSCRIPTEN_BINDINGS(capacitor_module) {
    emscripten::class_<Capacitor, emscripten::base<Component>>("Capacitor")
        .constructor<double, double>()
        .function("getComponentValue", &Capacitor::getComponentValue)
        .function("getAngularFrequency", &Capacitor::getAngularFrequency)
        .function("setComponentValue", &Capacitor::setComponentValue)
        .function("setAngularFrequency", &Capacitor::setAngularFrequency)
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
