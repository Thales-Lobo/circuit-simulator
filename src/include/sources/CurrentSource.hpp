#ifndef CURRENTSOURCE_HPP
#define CURRENTSOURCE_HPP

#include "sources/Source.hpp"

// Common interface for all current sources
class CurrentSource : virtual public Source {
public:
    virtual ~CurrentSource() {}
    virtual void setVoltage(std::complex<double> voltage) = 0;
};

#endif // CURRENTSOURCE_HPP
