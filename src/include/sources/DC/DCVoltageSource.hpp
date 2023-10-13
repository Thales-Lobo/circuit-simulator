#ifndef DCVOLTAGESOURCE_HPP
#define DCVOLTAGESOURCE_HPP

#include "sources/DC/DCSource.hpp"

class DCVoltageSource : public DCSource {
public:
    // Constructor
    DCVoltageSource(double value);
};

#endif // DCVOLTAGESOURCE_HPP
