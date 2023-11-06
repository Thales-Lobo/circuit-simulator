#ifndef VOLTAGESOURCE_HPP
#define VOLTAGESOURCE_HPP

#include "sources/Source.hpp"

// Common interface for all voltage sources
class VoltageSource : virtual public Source {
public:
    virtual ~VoltageSource() {}
    virtual void setCurrent(std::complex<double> current) = 0;
};

#endif // VOLTAGESOURCE_HPP
