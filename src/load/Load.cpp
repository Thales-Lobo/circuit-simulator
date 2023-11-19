#include "load/Load.hpp"

// Default constructor
Load::Load() = default;

// Constructor using value representation mode
Load::Load(double firstValue, double secondValue, RepresentationMode mode) {
    switch (mode) {
        case RepresentationMode::RECTANGULAR:
            impedance = {firstValue, secondValue};
            break;

        case RepresentationMode::POLAR_DEGREES: 
            impedance = std::polar(firstValue, secondValue * M_PI / 180.0);
            break;

        case RepresentationMode::POLAR_RADIANS:
            impedance = std::polar(firstValue, secondValue);
            break;
    }
    phase = std::arg(impedance);
}

// Calculate voltage and powers
void Load::calculateVoltage() {
    voltage = impedance * current;
    calculatePowers();
}

void Load::calculatePowers() {
    complexPower  = voltage * std::conj(current);
    activePower   = complexPower.real();
    reactivePower = complexPower.imag();
}

// Getters
std::complex<double> Load::getImpedance() const {
    return impedance;
}

std::complex<double> Load::getVoltage() const {
    return voltage;
}

std::complex<double> Load::getCurrent() const {
    return current;
}

std::complex<double> Load::getComplexPower() const {
    return complexPower;
}

double Load::getActivePower() const {
    return activePower;
}

double Load::getReactivePower() const {
    return reactivePower;
}

double Load::getPhase() const {
    return phase;
}

// Setter for current
void Load::setCurrent(std::complex<double> newCurrent) {
    if (current != newCurrent) {
        current = newCurrent;
        calculateVoltage();
    }
}
