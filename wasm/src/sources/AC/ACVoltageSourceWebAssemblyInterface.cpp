#include "sources/AC/ACVoltageSource.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

// Interface functions for creating and destroying ACVoltageSource objects
extern "C" {
    ACVoltageSource* CreateACVoltageSource(double firstValue, double secondValue, double thirdValue, 
                                            ACSource::ValueRepresentation valueMode, 
                                            ACSource::FrequencyRepresentation freqMode, 
                                            Load internalLoadParam) {
        return new ACVoltageSource(firstValue, secondValue, thirdValue, valueMode, freqMode, internalLoadParam);
    }

    void DestroyACVoltageSource(ACVoltageSource* acVoltageSource) {
        delete acVoltageSource;
    }
}

// Emscripten binding
EMSCRIPTEN_BINDINGS(ac_voltage_source_module) {
    class_<ACVoltageSource>("ACVoltageSource")
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
