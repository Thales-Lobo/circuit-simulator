#include "load/Load.hpp"

// Constructor
Load::Load() {};

Load::Load(double firstValue, double secondValue, RepresentationMode mode) {
    // Use a switch to determine the load's construction mode
    switch (mode) {
        // If the mode is RECTANGULAR, assumes that the values ​​provided are the real and imaginary part of the impedance
        case RepresentationMode::RECTANGULAR:
            this->impedance = std::complex<double>(firstValue, secondValue);
            break;

        // If the mode is POLAR_DEGREES, assumes that the values ​​provided are magnitude and phase (in degrees) of the impedance
        case RepresentationMode::POLAR_DEGREES: 
            this->impedance = std::polar(firstValue, secondValue * std::acos(-1) / 180.0);
            break;

        // If the mode is POLAR_RADIANS, assumes that the values ​​provided are magnitude and phase (in radians) of the impedance
        case RepresentationMode::POLAR_RADIANS:
            this->impedance = std::polar(firstValue, secondValue);
            break;
    }
    this->phase = std::arg(this->impedance);
}

// Calculations of electrical characteristics
void Load::calculateVoltage() {
    this->voltage = this->impedance * this->current;
    calculatePowers();
}

void Load::calculatePowers() {
    this->complexPower  = this->voltage * std::conj(this->current);
    this->activePower   = this->complexPower.real();
    this->reactivePower = this->complexPower.imag();
}

// Getters
std::complex<double> Load::getImpedance() {
    return impedance;
}

std::complex<double> Load::getVoltage() {
    return voltage;
}

std::complex<double> Load::getCurrent() {
    return current;
}

std::complex<double> Load::getComplexPower() {
    return complexPower;
}

double Load::getActivePower() {
    return activePower;
}

double Load::getReactivePower() {
    return reactivePower;
}

double Load::getPhase() {
    return phase;
}

// Setters
void Load::setVoltage(std::complex<double> voltage) {
    this->voltage = voltage;
}

void Load::setCurrent(std::complex<double> current) {
    this->current = current;
    calculateVoltage();
}

void Load::setComplexPower(std::complex<double> complexPower) {
    this->complexPower = complexPower;
}

void Load::setActivePower(double activePower) {
    this->activePower = activePower;
}

void Load::setReactivePower(double reactivePower) {
    this->reactivePower = reactivePower;
}

void Load::setPhase(double phase) {
    this->phase = phase;
}
