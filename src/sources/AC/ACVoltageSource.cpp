#include "sources/AC/ACVoltageSource.hpp"

// Constructor using amplitude, frequency, and phase
ACVoltageSource::ACVoltageSource(double amplitude, double frequency, double phase)
    : ACSource(amplitude, frequency, phase) {}

// Constructor using phasor and frequency
ACVoltageSource::ACVoltageSource(std::complex<double> phasor, double frequency)
    : ACSource(phasor, frequency) {}
