#ifndef CAPACITOR_HPP
#define CAPACITOR_HPP

#include "load/components/Component.hpp"

class Capacitor : public Component {
public:
    // Constructor
    Capacitor(double capacitanceValue, double angularFrequency);
};

#endif // CAPACITOR_HPP
