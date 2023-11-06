#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "load/Load.hpp"

/**
 * @file Component.hpp
 *
 * The Component class is an abstract representation of an electrical component.
 * It is derived from the Load class and provides a base for specific components
 * like resistors, capacitors, and inductors. It includes properties common to
 * these components, such as value and angular frequency.
 */

class Component : public Load {
protected:
    /**
     * @brief The value of the component.
     *
     * This could represent resistance in ohms for a resistor, capacitance in farads
     * for a capacitor, or inductance in henrys for an inductor.
     */
    double componentValue;

    /**
     * @brief The angular frequency at which the component operates.
     *
     * Angular frequency is related to the frequency of the electrical current
     * and is used to calculate the reactive properties of capacitors and inductors.
     */
    double angularFrequency;

public:
    /**
     * @brief Default constructor for the Component class.
     *
     * Initializes a new instance of the Component class with default values.
     */
    Component();

    /**
     * @brief Parameterized constructor for the Component class.
     *
     * Initializes a new instance of the Component class with specified values
     * for the component's value and angular frequency.
     *
     * @param componentValue The value of the component (resistance, capacitance, or inductance).
     * @param angularFrequency The angular frequency at which the component operates.
     */
    Component(double componentValue, double angularFrequency);
    
    /**
     * @brief Getter for the component's value.
     *
     * @return The value of the component.
     */
    double getComponentValue() const;

    /**
     * @brief Getter for the component's angular frequency.
     *
     * @return The angular frequency of the component.
     */
    double getAngularFrequency() const;
    
    /**
     * @brief Setter for the component's value.
     *
     * @param componentValue The new value for the component.
     */
    void setComponentValue(double componentValue);

    /**
     * @brief Setter for the component's angular frequency.
     *
     * @param angularFrequency The new angular frequency for the component.
     */
    void setAngularFrequency(double angularFrequency);
};

#endif // COMPONENT_HPP
