#ifndef DCCURRENTSOURCE_HPP
#define DCCURRENTSOURCE_HPP

#include "sources/DC/DCSource.hpp"
#include "sources/CurrentSource.hpp"

/**
 * @file DCCurrentSource.hpp
 *
 * Declares the DCCurrentSource class, which is a specific type of DCSource representing a DC current source.
 * It inherits from DCSource and allows setting of voltage in addition to current source parameters.
 */

class DCCurrentSource : public DCSource, public CurrentSource {
public:
    /**
     * @brief Constructs a DC current source with a specified current value.
     *
     * This constructor initializes a DC current source with the given current value. The value
     * represents the magnitude of the current flowing through the source.
     *
     * @param value The magnitude of the current for the DC current source.
     */
    DCCurrentSource(double value);

    /**
     * @brief Sets the voltage across the DC current source.
     *
     * This setter method allows the voltage across the DC current source to be specified.
     * The voltage is a complex number representing both the magnitude and phase of the voltage,
     * although for a DC source, the phase should typically be zero.
     *
     * @param voltage The complex voltage value to be set for the DC current source.
     */
    void setVoltage(std::complex<double> voltage) override;
};

#endif // DCCURRENTSOURCE_HPP
