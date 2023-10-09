#include "load/components/Resistor.hpp"

// Constructor
Resistor::Resistor(double resistanceValue, double angularFrequency) 
    : Component(resistanceValue, angularFrequency) {
        this->impedance = std::complex<double>(this->componentValue, 0.0);
}
