#ifndef ACCURRENTSOURCE_HPP
#define ACCURRENTSOURCE_HPP

#include "sources/AC/ACSource.hpp"
#include "sources/CurrentSource.hpp"

/**
 * @file ACCurrentSource.hpp
 *
 * Defines the ACCurrentSource class, which represents an alternating current (AC) source
 * that provides a current with a specific amplitude, frequency, and phase.
 */

class ACCurrentSource : public ACSource, public CurrentSource {
public:
    /**
     * @brief Constructs an AC current source with specified parameters.
     *
     * This constructor initializes an AC current source with given amplitude, frequency,
     * and phase. The representation of these values can be in rectangular or polar form,
     * and the frequency can be specified in hertz or radians per second.
     *
     * @param firstValue The amplitude of the current or the real part if in rectangular mode.
     * @param secondValue The frequency in hertz or the imaginary part if in rectangular mode.
     * @param thirdValue The phase of the current in degrees or radians.
     * @param valueMode The representation of the amplitude and phase (default is polar degrees).
     * @param freqMode The representation of the frequency (default is frequency in hertz).
     */
    ACCurrentSource(double firstValue, double secondValue, double thirdValue, 
                    ACSource::ValueRepresentation valueMode = ACSource::ValueRepresentation::POLAR_DEGREES, 
                    ACSource::FrequencyRepresentation freqMode = ACSource::FrequencyRepresentation::FREQUENCY);

    /**
     * @brief Sets the voltage across the AC current source.
     *
     * This method allows setting the voltage across the AC current source, which can be
     * used in conjunction with the current to calculate power and other electrical properties.
     *
     * @param voltage The complex voltage value to set.
     */
    void setVoltage(std::complex<double> voltage) override;
};

#endif // ACCURRENTSOURCE_HPP
