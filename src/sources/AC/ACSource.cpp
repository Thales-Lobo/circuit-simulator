#include "sources/AC/ACSource.hpp"

// Constructor for ACSource using amplitude, frequency, and phase.
// It initializes member variables based on the given value and frequency representations.
ACSource::ACSource(double firstValue, double secondValue, double thirdValue, 
                   ValueRepresentation valueMode, FrequencyRepresentation freqMode,
                   Load internalLoadParam)
    : amplitude(determineValue(firstValue, secondValue, valueMode).real()),
      frequency(determineFrequency(thirdValue, freqMode)),
      angularFrequency(2 * M_PI * frequency),
      phase(determineValue(firstValue, secondValue, valueMode).imag()),
      value(amplitude, phase)
{
    setInternalLoad(internalLoadParam);
}

// Handles the value representation based on mode and converts to a complex number.
std::complex<double> ACSource::determineValue(double magnitude, double angle, ValueRepresentation mode) {
    if (mode == ValueRepresentation::RECTANGULAR) {
        return std::complex<double>(magnitude, angle);
    }

    // Adjust magnitude and angle for polar coordinates, taking into account negative magnitudes.
    double adjustedMagnitude = std::abs(magnitude);
    double adjustedAngle = angle + (magnitude < 0 ? (mode == ValueRepresentation::POLAR_DEGREES ? 180 : M_PI) : 0);
    double angleInRadians = mode == ValueRepresentation::POLAR_DEGREES ? adjustedAngle * M_PI / 180 : adjustedAngle;

    return std::polar(adjustedMagnitude, angleInRadians);
}

// Determines the frequency based on the provided mode.
double ACSource::determineFrequency(double freqValue, FrequencyRepresentation mode) {
    // Convert angular frequency to regular frequency if needed.
    return mode == FrequencyRepresentation::ANGULAR_FREQUENCY ? freqValue / (2 * M_PI) : freqValue;
}


// Getters
double ACSource::getFrequency() {
    return frequency;
}

std::complex<double> ACSource::getValue() {
    return value;
}
