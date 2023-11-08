#include "sources/AC/ACVoltageSource.hpp"

// Constructor using amplitude, frequency, and phase
ACVoltageSource::ACVoltageSource(double firstValue, double secondValue, double thirdValue, 
                                 ACSource::ValueRepresentation valueMode, 
                                 ACSource::FrequencyRepresentation freqMode,
                                 Load internalLoad)
    : ACSource(firstValue, secondValue, thirdValue, valueMode, freqMode, internalLoad) {
        voltage = value;
    }

void ACVoltageSource::setCurrent(std::complex<double> newCurrent) {
    if (Source::current != newCurrent) {
        Source::current = newCurrent;
        Source::calculatePowers();
    }
}