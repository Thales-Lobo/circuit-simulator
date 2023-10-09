#include "load/components/Capacitor.hpp"

// Constructor
Capacitor::Capacitor(double capacitanceValue, double angularFrequency) 
    : Component(capacitanceValue, angularFrequency) {
        if (this->angularFrequency != 0.0 ) {
            if(this->componentValue != 0.0) {
                this->impedance = std::complex<double>(0.0, -1 / (this->angularFrequency * this->componentValue));
            } else{
                throw std::runtime_error("Invalid component value!");
            }
        } else{
            throw std::runtime_error("Invalid angular frequency value!");
        }
}
