#ifndef DCCURRENTSOURCE_HPP
#define DCCURRENTSOURCE_HPP

#include "sources/DC/DCSource.hpp"

/**
 * @file DCCurrentSource.hpp
 *
 * Declares the DCCurrentSource class, which is a specific type of DCSource representing a DC current source.
 * It inherits from DCSource and allows setting of voltage in addition to current source parameters.
 */

class DCCurrentSource : public DCSource {
public:
    /**
     * @brief Constructs a DC current source with a specified current value.
     *
     * This constructor initializes a DC current source with the given current value. The value
     * represents the magnitude of the current flowing through the source.
     *
     * @param value The magnitude of the current for the DC current source.
     */
    DCCurrentSource(double value, Load internalLoadParam = Load(0.0, 0.0, Load::RepresentationMode::POLAR_DEGREES));

};

#endif // DCCURRENTSOURCE_HPP
