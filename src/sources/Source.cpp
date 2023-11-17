#include "sources/Source.hpp"

//Destructor
Source::~Source() {}

// Calculate all source powers
void Source::calculatePowers() {
    complexPower    = voltage * std::conj(current);
    activePower     = complexPower.real();
    reactivePower   = complexPower.imag();
    phase           = std::arg(complexPower);
}

// Getters
std::complex<double> Source::getInternalLoad() const {
    return internalLoad.getImpedance();
}

std::complex<double> Source::getVoltage() const {
    return voltage;
}

std::complex<double> Source::getCurrent() const {
    return current;
}

std::complex<double> Source::getComplexPower() const {
    return complexPower;
}

double Source::getActivePower() const {
    return activePower;
}

double Source::getReactivePower() const {
    return reactivePower;
}

double Source::getPhase() const {
    return phase;
}

// Setters
void Source::setInternalLoad(Load internalLoadParam) {
    internalLoad = internalLoadParam;
}

void Source::setVoltage(std::complex<double> newVoltage) {
    if (voltage != newVoltage) {
        voltage = newVoltage;
        calculatePowers();
    }
}

void Source::setCurrent(std::complex<double> newCurrent) {
    if (current != newCurrent) {
        current = newCurrent;
        calculatePowers();
    }
}
