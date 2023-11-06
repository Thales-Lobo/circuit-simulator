#ifndef CAPACITOR_HPP
#define CAPACITOR_HPP

#include "load/components/Component.hpp"

/**
 * @file Capacitor.hpp
 *
 * The Capacitor class represents a capacitor component in an electrical circuit.
 * It inherits from the Component class and is characterized by its capacitance value.
 * The impedance of a capacitor is inversely related to the angular frequency of the current passing through it.
 */

class Capacitor : public Component {
public:
    /**
     * @brief Constructor for the Capacitor class.
     *
     * Creates a Capacitor object with a specified capacitance value and operating angular frequency.
     * The impedance of the capacitor is calculated based on these values, considering the capacitive
     * reactance formula Xc = 1 / (ωC), where ω is the angular frequency and C is the capacitance.
     *
     * @param capacitanceValue The capacitance value of the capacitor in farads (F).
     * @param angularFrequency The angular frequency (in radians per second) at which the
     *        capacitor operates. This value is used to calculate the reactive impedance of the capacitor.
     */
    Capacitor(double capacitanceValue, double angularFrequency);
};

#endif // CAPACITOR_HPP
