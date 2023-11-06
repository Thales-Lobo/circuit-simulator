#ifndef RESISTOR_HPP
#define RESISTOR_HPP

#include "load/components/Component.hpp"

/**
 * @file Resistor.hpp
 *
 * The Resistor class represents a resistor component in an electrical circuit.
 * It inherits from the Component class and is characterized by its resistance value.
 */

class Resistor : public Component {
public:
    /**
     * @brief Constructor for the Resistor class.
     *
     * Creates a Resistor object with a specified resistance value. The angular frequency
     * is not relevant for a resistor as it does not change with frequency, but it is
     * provided here for compatibility with the Component interface.
     *
     * @param resistanceValue The resistance value of the resistor in ohms.
     * @param angularFrequency The angular frequency (in radians per second) at which the
     *        resistor operates. Default is 0.0, indicating DC or no frequency dependence.
     */
    Resistor(double resistanceValue, double angularFrequency = 0.0);
};

#endif // RESISTOR_HPP
