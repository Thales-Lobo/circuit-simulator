#include "sources/DC/DCCurrentSource.hpp"

// Constructor
DCCurrentSource::DCCurrentSource(double value)
    : DCSource(value) {
        current = value;
    }

void DCCurrentSource::setVoltage(std::complex<double> newVoltage) {
    if (Source::voltage != newVoltage) {
        Source::voltage = newVoltage;
        Source::calculatePowers();
    }
}