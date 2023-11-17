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
protected:
    /**
     * @enum ValueRepresentation
     * Represents the different ways in which the value of an AC source can be expressed.
     */
    enum class ValueRepresentation {
        RECTANGULAR,      ///< Represent value as a complex number in rectangular form.
        POLAR_DEGREES,    ///< Represent value as a magnitude and phase in degrees.
        POLAR_RADIANS     ///< Represent value as a magnitude and phase in radians.
    };

    /**
     * @enum FrequencyRepresentation
     * Represents the different ways in which the frequency of an AC source can be expressed.
     */
    enum class FrequencyRepresentation {
        FREQUENCY,        ///< Represent frequency in hertz (cycles per second).
        ANGULAR_FREQUENCY ///< Represent angular frequency in radians per second.
    };

    /**
     * @brief Determines the complex value of the AC source.
     * 
     * This method calculates the complex number representing the AC source
     * based on the magnitude and angle, taking into account the representation mode
     * (either in rectangular or polar form).
     *
     * @param magnitude The magnitude of the complex number. In polar mode, it's the radius;
     *                  in rectangular mode, it's the real part.
     * @param angle The angle of the complex number. In polar mode, it's the phase angle;
     *              in rectangular mode, it's the imaginary part.
     * @param mode The representation mode of the value (RECTANGULAR or POLAR).
     * @return std::complex<double> The calculated complex value.
     */
    std::complex<double> determineValue(double magnitude, double angle, ValueRepresentation mode);
    
    /**
     * @brief Determines the frequency of the AC source.
     * 
     * This method converts the given frequency value into the actual frequency
     * of the AC source, based on the specified representation mode.
     * It supports direct frequency or angular frequency input.
     *
     * @param freqValue The input frequency value. This can be either the regular frequency
     *                  or angular frequency, depending on the mode.
     * @param mode The frequency representation mode (FREQUENCY or ANGULAR_FREQUENCY).
     * @return double The actual frequency of the AC source.
     */
    double determineFrequency(double freqValue, FrequencyRepresentation mode);

    double amplitude;              ///< The maximum value of the current or voltage.
    double frequency;              ///< The frequency in hertz at which the source operates.
    double angularFrequency;       ///< The angular frequency in radians per second.
    double phase;                  ///< The phase shift of the source in degrees or radians.
    std::complex<double> value;    ///< The complex value representing the source in rectangular form.

public:
    /**
     * @brief Constructs an AC source with specified parameters.
     *
     * Initializes an AC source with given amplitude, frequency, and phase. The values can be
     * represented in either rectangular or polar form, and frequency can be specified in hertz
     * or radians per second.
     *
     * @param firstValue The amplitude of the source or the real part if in rectangular mode.
     * @param secondValue The frequency in hertz or the imaginary part if in rectangular mode.
     * @param thirdValue The phase of the source in degrees or radians.
     * @param valueMode The representation of the amplitude and phase (default is polar degrees).
     * @param freqMode The representation of the frequency (default is frequency in hertz).
     * @param internalLoadParam The internal load of the source (default is a load with zero impedance).
     */
    ACSource(double firstValue, double secondValue, double thirdValue, 
             ValueRepresentation valueMode = ValueRepresentation::POLAR_DEGREES, 
             FrequencyRepresentation freqMode = FrequencyRepresentation::FREQUENCY,
             Load internalLoadParam = Load(0.0, 0.0, Load::RepresentationMode::POLAR_DEGREES));

    /**
     * @brief Virtual destructor for the ACSource class.
     */
    virtual ~ACSource() override = default;

    /**
     * @brief Gets the frequency of the AC source.
     *
     * This function returns the frequency of the AC source in hertz.
     *
     * @return The frequency in hertz.
     */
    virtual double getFrequency();

    /**
     * @brief Gets the complex value of the AC source.
     *
     * This function returns the complex value of the AC source, which represents
     * the amplitude and phase in rectangular form.
     *
     * @return The complex value of the AC source.
     */
    virtual std::complex<double> getValue();
};

#endif // ACSOURCE_HPP
