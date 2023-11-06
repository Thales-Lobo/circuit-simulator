#ifndef INDUCTOR_HPP
#define INDUCTOR_HPP

#include "load/components/Component.hpp"

class Inductor : public Component {
public:
    // Constructor
    Inductor(double inductanceValue, double angularFrequency);
};

#endif // INDUCTOR_HPP
