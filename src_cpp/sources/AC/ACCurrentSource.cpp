#include "sources/AC/ACCurrentSource.hpp"

// Constructor using amplitude, frequency, and phase
ACCurrentSource::ACCurrentSource(double firstValue, double secondValue, double thirdValue, 
                                 ACSource::ValueRepresentation valueMode, 
                                 ACSource::FrequencyRepresentation freqMode)
    : ACSource(firstValue, secondValue, thirdValue, valueMode, freqMode) {}
