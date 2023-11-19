#include "sources/DC/DCVoltageSource.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

// Interface functions for creating and destroying DCVoltageSource objects
extern "C" {
    DCVoltageSource* CreateDCVoltageSource(double value, Load internalLoadParam) {
        return new DCVoltageSource(value, internalLoadParam);
    }

    void DestroyDCVoltageSource(DCVoltageSource* dcVoltageSource) {
        delete dcVoltageSource;
    }
}

// Emscripten binding
EMSCRIPTEN_BINDINGS(dc_voltage_source_module) {
    class_<DCVoltageSource>("DCVoltageSource")
        .constructor<double, Load>()
        // Inherited functions from DCSource
        .function("getValue", &DCSource::getValue)
        // Inherited functions from Source
        .function("getInternalLoad", &Source::getInternalLoad)
        .function("getVoltage", &Source::getVoltage)
        .function("getCurrent", &Source::getCurrent)
        .function("getComplexPower", &Source::getComplexPower)
        .function("getActivePower", &Source::getActivePower)
        .function("getReactivePower", &Source::getReactivePower)
        .function("getPhase", &Source::getPhase)
        .function("setInternalLoad", &Source::setInternalLoad)
        .function("setVoltage", &Source::setVoltage)
        .function("setCurrent", &Source::setCurrent);
}
