#include "ACCurrentSource.hpp"

// Constructor using amplitude, frequency, and phase
ACCurrentSource::ACCurrentSource(double amplitude, double frequency, double phase)
    : ACSource(amplitude, frequency, phase) {}

// Constructor using phasor and frequency
ACCurrentSource::ACCurrentSource(std::complex<double> phasor, double frequency)
    : ACSource(phasor, frequency) {}
