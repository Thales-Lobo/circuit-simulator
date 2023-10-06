#include "components/Capacitor.hpp"

// Constructor
Capacitor::Capacitor(double firstValue, double secondValue, ComponentMode mode) 
    : Component(firstValue, secondValue, mode) {}

void Capacitor::calculateImpedance() {
    this->impedance = std::complex<double>(0.0, -1 / (this->angularFrequency * this->componentValue));
}

void Capacitor::calculateComponentValue() {
    this->componentValue = 1 / (abs(this->impedance) * this->angularFrequency);
}
