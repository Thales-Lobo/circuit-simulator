#ifndef DCVOLTAGESOURCE_HPP
#define DCVOLTAGESOURCE_HPP

#include "sources/DC/DCSource.hpp"
#include "sources/VoltageSource.hpp"

/**
 * @file DCVoltageSource.hpp
 *
 * Declares the DCVoltageSource class, which represents a direct current (DC) voltage source
 * in an electrical circuit simulation. It inherits from the DCSource class.
 */

class DCVoltageSource : public DCSource, public VoltageSource {
public:
    /**
     * @brief Constructs a DC voltage source with a specified voltage value.
     *
     * This constructor initializes a DC voltage source with the given voltage magnitude.
     * The voltage is specified as a double-precision floating-point number.
     *
     * @param value The magnitude of the voltage provided by the source.
     */
    DCVoltageSource(double value);

    /**
     * @brief Sets the current through the DC voltage source.
     *
     * This function allows setting the current that flows through the voltage source,
     * which can be useful in certain simulation scenarios where the current needs to be
     * controlled or monitored.
     *
     * @param current The complex current value to be set, typically the real part represents
     *                the current magnitude and the imaginary part is zero for DC sources.
     */
    void setCurrent(std::complex<double> current) override;
};

#endif // DCVOLTAGESOURCE_HPP
