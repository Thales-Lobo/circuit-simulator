#include "sources/DC/DCVoltageSource.hpp"

// Constructor
DCVoltageSource::DCVoltageSource(double value, Load internalLoad)
    : DCSource(value, internalLoad) {
        voltage = value;
    }

void DCVoltageSource::setCurrent(std::complex<double> newCurrent) {
    if (Source::current != newCurrent) {
        Source::current = newCurrent;
        Source::calculatePowers();
    }
}
