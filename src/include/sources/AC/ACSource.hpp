#ifndef ACSOURCE_HPP
#define ACSOURCE_HPP

#include "sources/Source.hpp"

class ACSource : public Source {
protected:
    // Protected classes
    enum class ValueRepresentation {
        RECTANGULAR,
        POLAR_DEGREES,
        POLAR_RADIANS
    };
    enum class FrequencyRepresentation {
        FREQUENCY,
        ANGULAR_FREQUENCY
    };

    // Protected fields
    double amplitude;
    double frequency;
    double angularFrequency;
    double phase;
    std::complex<double> phasor;

public:
    // Constructor
    ACSource(double firstValue, double secondValue, double thirdValue, 
                        ValueRepresentation valueMode = ValueRepresentation::POLAR_DEGREES, 
                        FrequencyRepresentation freqMode = FrequencyRepresentation::FREQUENCY);

    // Functions
    virtual double getFrequency();
    virtual std::complex<double> getValue();
};

#endif // ACSOURCE_HPP
