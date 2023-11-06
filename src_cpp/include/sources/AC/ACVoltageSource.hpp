#ifndef ACVOLTAGESOURCE_HPP
#define ACVOLTAGESOURCE_HPP

#include "sources/AC/ACSource.hpp"

class ACVoltageSource : public ACSource {
public:
    // Constructor using amplitude, frequency, and phase
    ACVoltageSource(double firstValue, double secondValue, double thirdValue, 
                    ACSource::ValueRepresentation valueMode = ACSource::ValueRepresentation::POLAR_DEGREES, 
                    ACSource::FrequencyRepresentation freqMode = ACSource::FrequencyRepresentation::FREQUENCY);
};

#endif // ACVOLTAGESOURCE_HPP
