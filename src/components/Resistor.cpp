#include "components/Resistor.hpp"

// Constructor
Resistor::Resistor(double firstValue, double secondValue, ComponentMode mode) 
    : Component(firstValue, secondValue, mode) {}

void Resistor::calculateImpedance() {
    this->impedance = std::complex<double>(this->componentValue, 0.0);
}

void Resistor::calculateComponentValue() {
    this->componentValue = this->impedance.real();
}
