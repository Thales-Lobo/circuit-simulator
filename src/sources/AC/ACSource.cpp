#include "sources/AC/ACSource.hpp"

// Constructor using amplitude, frequency, and phase
ACSource::ACSource(double amplitude, double frequency, double phase) {
    this->amplitude = amplitude;
    this->frequency = frequency;
    this->phase     = phase;
    this->phasor    = std::polar(amplitude, phase);
}

// Constructor using phasor and frequency
ACSource::ACSource(std::complex<double> phasor, double frequency) {
    this->phasor    = phasor;
    this->frequency = frequency;
    this->amplitude = std::abs(phasor);
    this->phase     = std::arg(phasor);
}

std::complex<double> ACSource::getValue() {
    return this->phasor;
}
