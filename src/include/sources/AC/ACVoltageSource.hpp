#ifndef ACVOLTAGESOURCE_HPP
#define ACVOLTAGESOURCE_HPP

#include "sources/VoltageSource.hpp"
#include "sources/AC/ACSource.hpp"

/**
 * @file ACVoltageSource.hpp
 *
 * Declares the ACVoltageSource class, which is a specific type of ACSource representing an AC voltage source.
 * It inherits from ACSource and allows setting of current in addition to voltage source parameters.
 */

class ACVoltageSource : public ACSource, public VoltageSource {
public:
    /**
     * @brief Constructs an AC voltage source with specified amplitude, frequency, and phase.
     *
     * This constructor initializes an AC voltage source with the given parameters. The values can be
     * represented in either rectangular or polar form, and frequency can be specified in hertz
     * or radians per second.
     *
     * @param firstValue The amplitude of the voltage source or the real part if in rectangular mode.
     * @param secondValue The frequency in hertz or the imaginary part if in rectangular mode.
     * @param thirdValue The phase of the voltage source in degrees or radians.
     * @param valueMode The representation of the amplitude and phase (default is polar degrees).
     * @param freqMode The representation of the frequency (default is frequency in hertz).
     */
    ACVoltageSource(double firstValue, double secondValue, double thirdValue, 
                    ACSource::ValueRepresentation valueMode = ACSource::ValueRepresentation::POLAR_DEGREES, 
                    ACSource::FrequencyRepresentation freqMode = ACSource::FrequencyRepresentation::FREQUENCY,
                    Load internalLoad = Load(0.0, 0.0, Load::RepresentationMode::POLAR_DEGREES));

    /**
     * @brief Sets the current flowing through the AC voltage source.
     *
     * This setter method allows the current flowing through the AC voltage source to be specified.
     * The current is a complex number representing both the magnitude and phase of the current.
     *
     * @param current The complex current value to be set for the AC voltage source.
     */
    void setCurrent(std::complex<double> current) override;
};

#endif // ACVOLTAGESOURCE_HPP
