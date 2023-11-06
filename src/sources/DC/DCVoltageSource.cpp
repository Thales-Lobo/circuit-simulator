#include "sources/DC/DCVoltageSource.hpp"

// Constructor
DCVoltageSource::DCVoltageSource(double value)
    : DCSource(value) {
        voltage = value;
    }

void DCVoltageSource::setCurrent(std::complex<double> newCurrent) {
    if (Source::current != newCurrent) {
        Source::current = newCurrent;
        Source::calculatePowers();
    }
}
