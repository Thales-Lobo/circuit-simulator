#include "sources/DC/DCCurrentSource.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

// Interface functions for creating and destroying DCCurrentSource objects
extern "C" {
    DCCurrentSource* CreateDCCurrentSource(double value, Load internalLoadParam) {
        return new DCCurrentSource(value, internalLoadParam);
    }

    void DestroyDCCurrentSource(DCCurrentSource* dcCurrentSource) {
        delete dcCurrentSource;
    }
}

// Emscripten binding
EMSCRIPTEN_BINDINGS(dc_current_source_module) {
    class_<DCCurrentSource>("DCCurrentSource")
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
