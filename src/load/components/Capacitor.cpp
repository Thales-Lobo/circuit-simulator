#include "load/components/Capacitor.hpp"

// Constructor
Capacitor::Capacitor(double capacitanceValue, double angularFrequency) 
    : Component(capacitanceValue, angularFrequency) {
        
    impedance = std::complex<double>(0.0, -1 / (angularFrequency * componentValue));
}
