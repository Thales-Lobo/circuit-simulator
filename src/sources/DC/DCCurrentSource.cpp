#include "sources/DC/DCCurrentSource.hpp"

// Constructor
DCCurrentSource::DCCurrentSource(double value, Load internalLoad)
    : DCSource(value, internalLoad) {
        current = value;
    }

void DCCurrentSource::setVoltage(std::complex<double> newVoltage) {
    if (Source::voltage != newVoltage) {
        Source::voltage = newVoltage;
        Source::calculatePowers();
    }
}