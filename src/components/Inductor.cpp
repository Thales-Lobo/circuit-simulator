#include "Inductor.hpp"

// Constructor
Inductor::Inductor(double firstValue, double secondValue, ComponentMode mode) 
    : Component(firstValue, secondValue, mode) {}

void Inductor::calculateImpedance() {
    this->impedance = std::complex<double>(0.0, this->angularFrequency * this->componentValue);
}

void Inductor::calculateComponentValue() {
    this->componentValue = abs(this->impedance) / this->angularFrequency;
}
