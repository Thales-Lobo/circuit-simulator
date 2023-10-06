#ifndef RESISTOR_HPP
#define RESISTOR_HPP

#include "components/Component.hpp"

class Resistor : public Component {
public:
    // Constructor
    Resistor(double firstValue, double secondValue, ComponentMode mode = ComponentMode::RECTANGULAR);

protected:
    void calculateImpedance() override;
    void calculateComponentValue() override;
};

#endif // RESISTOR_HPP
