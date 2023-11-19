#ifndef ACSOURCE_HPP
#define ACSOURCE_HPP

#include "sources/Source.hpp"
#include <complex>

/**
 * @file ACSource.hpp
 *
 * Declares the ACSource class, which serves as a base class for all alternating current (AC) sources.
 * It provides common attributes and functionality for AC sources, such as amplitude, frequency, and phase.
 */

class ACSource : virtual public Source {
public:
    enum class ValueRepresentation {
        RECTANGULAR,      ///< Represent value as a complex number in rectangular form.
        POLAR_DEGREES,    ///< Represent value as a magnitude and phase in degrees.
        POLAR_RADIANS     ///< Represent value as a magnitude and phase in radians.
    };

    enum class FrequencyRepresentation {
        FREQUENCY,        ///< Represent frequency in hertz (cycles per second).
        ANGULAR_FREQUENCY ///< Represent angular frequency in radians per second.
    };

    ACSource(double firstValue, double secondValue, double thirdValue, 
             ValueRepresentation valueMode = ValueRepresentation::POLAR_DEGREES, 
             FrequencyRepresentation freqMode = FrequencyRepresentation::FREQUENCY,
             Load internalLoadParam = Load(0.0, 0.0, Load::RepresentationMode::POLAR_DEGREES));

    virtual ~ACSource() override = default;

    virtual double getFrequency();
    virtual std::complex<double> getValue();

protected:
    std::complex<double> determineValue(double magnitude, double angle, ValueRepresentation mode);
    double determineFrequency(double freqValue, FrequencyRepresentation mode);

    double amplitude;              ///< The maximum value of the current or voltage.
    double frequency;              ///< The frequency in hertz at which the source operates.
    double angularFrequency;       ///< The angular frequency in radians per second.
    double phase;                  ///< The phase shift of the source in degrees or radians.
    std::complex<double> value;    ///< The complex value representing the source in rectangular form.
};

#endif // ACSOURCE_HPP
