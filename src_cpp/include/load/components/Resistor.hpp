#ifndef RESISTOR_HPP
#define RESISTOR_HPP

#include "load/components/Component.hpp"

class Resistor : public Component {
public:
    // Constructor
    Resistor(double resistanceValue, double angularFrequency = 0.0);
};

#endif // RESISTOR_HPP
