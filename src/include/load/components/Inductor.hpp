#ifndef INDUCTOR_HPP
#define INDUCTOR_HPP

#include "load/components/Component.hpp"

/**
 * @file Inductor.hpp
 *
 * The Inductor class represents an inductor component in an electrical circuit.
 * It inherits from the Component class and is characterized by its inductance value.
 * The impedance of an inductor depends on the angular frequency of the current passing through it.
 */

class Inductor : public Component {
public:
    /**
     * @brief Constructor for the Inductor class.
     *
     * Creates an Inductor object with a specified inductance value and operating angular frequency.
     * The impedance of the inductor is calculated based on these values.
     *
     * @param inductanceValue The inductance value of the inductor in henrys (H).
     * @param angularFrequency The angular frequency (in radians per second) at which the
     *        inductor operates. This value is used to calculate the reactive impedance of the inductor.
     */
    Inductor(double inductanceValue, double angularFrequency);
};

#endif // INDUCTOR_HPP
