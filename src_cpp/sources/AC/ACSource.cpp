#include "sources/AC/ACSource.hpp"

// Constructor using amplitude, frequency, and phase
ACSource::ACSource(double firstValue, double secondValue, double thirdValue, 
                    ValueRepresentation valueMode, FrequencyRepresentation freqMode) {

    // Handle value representation
    switch (valueMode) {
        // Set phasor using rectangular coordinates
        case ValueRepresentation::RECTANGULAR:
            this->phasor = std::complex<double>(firstValue, secondValue); 
            break;

        // Set phasor using polar coordinates (degrees)
        case ValueRepresentation::POLAR_DEGREES:
            this->phasor = std::polar(firstValue, secondValue * PI / 180); 
            break;

        // Set phasor using polar coordinates (radians)
        case ValueRepresentation::POLAR_RADIANS:
            this->phasor = std::polar(firstValue, secondValue); 
            break;
    }

    // Handle frequency representation
    switch (freqMode) {
        // Set frequency directly
        case FrequencyRepresentation::FREQUENCY:
            this->frequency = thirdValue; 
            break;

        // Convert angular frequency to regular frequency
        case FrequencyRepresentation::ANGULAR_FREQUENCY:
            this->frequency = thirdValue / (2 * PI); 
            break;
    }

    // Common calculations
    this->amplitude = std::abs(phasor);
    this->phase = std::arg(phasor);
    this->angularFrequency = 2 * PI * this->frequency;
}

// Getters
double ACSource::getFrequency() {
    return this->frequency;
}

std::complex<double> ACSource::getValue() {
    return this->phasor;
}
