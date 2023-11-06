#include "load/components/Inductor.hpp"

// Constructor
Inductor::Inductor(double inductanceValue, double angularFrequency) 
    : Component(inductanceValue, angularFrequency) {
    this->impedance = std::complex<double>(0.0, this->angularFrequency * this->componentValue);
}
