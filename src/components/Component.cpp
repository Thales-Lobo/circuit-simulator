#include "components/Component.hpp"

// Constructor
Component::Component(double firstValue, double secondValue, ComponentMode mode) {
    // Use a switch to determine the component's construction mode
    switch (mode) {
        // If mode is VALUE_FREQUENCY, assumes the given values ​​are componentValue and angularFrequency
        case ComponentMode::VALUE_FREQUENCY:
            this->componentValue    = firstValue;
            this->angularFrequency  = secondValue;
            calculateImpedance();
            break;

        // If the mode is RECTANGULAR, assumes that the values ​​provided are the real and imaginary part of the impedance
        case ComponentMode::RECTANGULAR:
            this->impedance = std::complex<double>(firstValue, secondValue);
            calculateComponentValue();
            break;

        // If the mode is POLAR_DEGREES, assumes that the values ​​provided are magnitude and phase (in degrees) of the impedance
        case ComponentMode::POLAR_DEGREES: 
            this->impedance = std::polar(firstValue, secondValue * std::acos(-1) / 180.0);
            calculateComponentValue();
            break;

        // If the mode is POLAR_RADIANS, assumes that the values ​​provided are magnitude and phase (in radians) of the impedance
        case ComponentMode::POLAR_RADIANS:
            this->impedance = std::polar(firstValue, secondValue);
            calculateComponentValue();
            break;
    }
    this->phase = std::arg(this->impedance);
}

// Semi-virtual functions (can't call a virtual function on constructor)
void Component::calculateImpedance() {};
void Component::calculateComponentValue() {};

// Calculations of electrical characteristics
void Component::calculatePowers() {
    this->complexPower  = this->voltage * std::conj(this->current);
    this->activePower   = this->complexPower.real();
    this->reactivePower = this->complexPower.imag();
}

void Component::calculateVoltage() {
    this->voltage = this->impedance * this->current;
    calculatePowers();
}

// Getters
double Component::getComponentValue() {
    return componentValue;
}

double Component::getAngularFrequency() {
    return angularFrequency;
}

std::complex<double> Component::getImpedance() {
    return impedance;
}

std::complex<double> Component::getVoltage() {
    return voltage;
}

std::complex<double> Component::getCurrent() {
    return current;
}

std::complex<double> Component::getComplexPower() {
    return complexPower;
}

double Component::getActivePower() {
    return activePower;
}

double Component::getReactivePower() {
    return reactivePower;
}

double Component::getPhase() {
    return phase;
}

// Setters
void Component::setComponentValue(double componentValue) {
    this->componentValue = componentValue;
}

void Component::setAngularFrequency(double angularFrequency) {
    this->angularFrequency = angularFrequency;
}

void Component::setVoltage(std::complex<double> voltage) {
    this->voltage = voltage;
}

void Component::setCurrent(std::complex<double> current) {
    this->current = current;
    calculateVoltage();
}

void Component::setComplexPower(std::complex<double> complexPower) {
    this->complexPower = complexPower;
}

void Component::setActivePower(double activePower) {
    this->activePower = activePower;
}

void Component::setReactivePower(double reactivePower) {
    this->reactivePower = reactivePower;
}

void Component::setPhase(double phase) {
    this->phase = phase;
}
