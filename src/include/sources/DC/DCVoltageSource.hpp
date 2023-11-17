#ifndef DCVOLTAGESOURCE_HPP
#define DCVOLTAGESOURCE_HPP

#include "sources/DC/DCSource.hpp"

/**
 * @file DCVoltageSource.hpp
 *
 * Declares the DCVoltageSource class, which represents a direct current (DC) voltage source
 * in an electrical circuit simulation. It inherits from the DCSource class.
 */

class DCVoltageSource : public DCSource {
public:
    /**
     * @brief Constructs a DC voltage source with a specified voltage value.
     *
     * This constructor initializes a DC voltage source with the given voltage magnitude.
     * The voltage is specified as a double-precision floating-point number.
     *
     * @param value The magnitude of the voltage provided by the source.
     */
    DCVoltageSource(double value, Load internalLoadParam = Load(0.0, 0.0, Load::RepresentationMode::POLAR_DEGREES));

};

#endif // DCVOLTAGESOURCE_HPP
