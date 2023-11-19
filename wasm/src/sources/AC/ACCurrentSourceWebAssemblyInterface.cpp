#include "sources/AC/ACCurrentSource.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

// Interface functions for creating and destroying ACCurrentSource objects
extern "C" {
    ACCurrentSource* CreateACCurrentSource(double firstValue, double secondValue, double thirdValue, 
                                            ACSource::ValueRepresentation valueMode, 
                                            ACSource::FrequencyRepresentation freqMode, 
                                            Load internalLoadParam) {
        return new ACCurrentSource(firstValue, secondValue, thirdValue, valueMode, freqMode, internalLoadParam);
    }

    void DestroyACCurrentSource(ACCurrentSource* acCurrentSource) {
        delete acCurrentSource;
    }
}

// Emscripten binding
EMSCRIPTEN_BINDINGS(ac_current_source_module) {
    class_<ACCurrentSource>("ACCurrentSource")
        .constructor<double, double, double, ACSource::ValueRepresentation, ACSource::FrequencyRepresentation, Load>()
        // Inherited functions from ACSource
        .function("getFrequency", &ACSource::getFrequency)
        .function("getValue", &ACSource::getValue)
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
