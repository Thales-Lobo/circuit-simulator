#ifndef INDUCTOR_HPP
#define INDUCTOR_HPP

#include "Component.hpp"

class Inductor : public Component {
public:
    // Constructor
    Inductor(double firstValue, double secondValue, ComponentMode mode = ComponentMode::POLAR_DEGREES);

protected:
    void calculateImpedance() override;
    void calculateComponentValue() override;
};

#endif // INDUCTOR_HPP
