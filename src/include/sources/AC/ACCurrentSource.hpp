#ifndef ACCURRENTSOURCE_HPP
#define ACCURRENTSOURCE_HPP

#include "sources/AC/ACSource.hpp"

class ACCurrentSource : public ACSource {
public:
    // Constructor using amplitude, frequency, and phase
    ACCurrentSource(double firstValue, double secondValue, double thirdValue, 
                    ACSource::ValueRepresentation valueMode = ACSource::ValueRepresentation::POLAR_DEGREES, 
                    ACSource::FrequencyRepresentation freqMode = ACSource::FrequencyRepresentation::FREQUENCY);
};

#endif // ACCURRENTSOURCE_HPP
