#include "sources/AC/ACSource.hpp"

// Constructor using amplitude, frequency, and phase
ACSource::ACSource(double firstValue, double secondValue, double thirdValue, 
                    ValueRepresentation valueMode, FrequencyRepresentation freqMode, Load internalLoad) {

    // Handle value representation
    switch (valueMode) {
        // Set value using rectangular coordinates
        case ValueRepresentation::RECTANGULAR:
            value = std::complex<double>(firstValue, secondValue); 
            break;

        // Set value using polar coordinates (degrees)
        case ValueRepresentation::POLAR_DEGREES:
            value = std::polar(firstValue, secondValue * PI / 180); 
            break;

        // Set value using polar coordinates (radians)
        case ValueRepresentation::POLAR_RADIANS:
            value = std::polar(firstValue, secondValue); 
            break;
    }

    // Handle frequency representation
    switch (freqMode) {
        // Set frequency directly
        case FrequencyRepresentation::FREQUENCY:
            frequency = thirdValue; 
            break;

        // Convert angular frequency to regular frequency
        case FrequencyRepresentation::ANGULAR_FREQUENCY:
            frequency = thirdValue / (2 * PI); 
            break;
    }

    // Common calculations
    amplitude         = std::abs(value);
    phase             = std::arg(value);
    angularFrequency  = 2 * PI * frequency;
    internalLoad      = internalLoad;
}

// Getters
double ACSource::getFrequency() {
    return frequency;
}

std::complex<double> ACSource::getValue() {
    return value;
}
