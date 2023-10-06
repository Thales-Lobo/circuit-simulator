#ifndef CAPACITOR_HPP
#define CAPACITOR_HPP

#include "components/Component.hpp"

class Capacitor : public Component {
public:
    // Constructor
    Capacitor(double firstValue, double secondValue, ComponentMode mode = ComponentMode::POLAR_DEGREES);

protected:
    void calculateImpedance() override;
    void calculateComponentValue() override;
};

#endif // CAPACITOR_HPP
