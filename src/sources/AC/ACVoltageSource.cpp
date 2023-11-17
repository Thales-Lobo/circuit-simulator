#include "sources/AC/ACVoltageSource.hpp"

// Constructor using amplitude, frequency, and phase
ACVoltageSource::ACVoltageSource(double firstValue, double secondValue, double thirdValue, 
                                 ACSource::ValueRepresentation valueMode, 
                                 ACSource::FrequencyRepresentation freqMode,
                                 Load internalLoadParam)
    : ACSource(firstValue, secondValue, thirdValue, valueMode, freqMode, internalLoadParam) {
        voltage = value;
    }