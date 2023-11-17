#include "sources/DC/DCVoltageSource.hpp"

// Constructor
DCVoltageSource::DCVoltageSource(double valueParam, Load internalLoadParam)
    : DCSource(valueParam, internalLoadParam) {
        voltage = value;
    }
