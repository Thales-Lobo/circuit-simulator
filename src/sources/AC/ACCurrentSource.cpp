#include "sources/AC/ACCurrentSource.hpp"

// Constructor using amplitude, frequency, and phase
ACCurrentSource::ACCurrentSource(double firstValue, double secondValue, double thirdValue, 
                                 ACSource::ValueRepresentation valueMode, 
                                 ACSource::FrequencyRepresentation freqMode,
                                 Load internalLoad)
    : ACSource(firstValue, secondValue, thirdValue, valueMode, freqMode, internalLoad) {
        current = value;
    }

void ACCurrentSource::setVoltage(std::complex<double> newVoltage) {
    if (Source::voltage != newVoltage) {
        Source::voltage = newVoltage;
        Source::calculatePowers();
    }
}
