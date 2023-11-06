#ifndef DCSOURCE_HPP
#define DCSOURCE_HPP

#include "sources/Source.hpp"

class DCSource : public Source {
protected:
    // Protected fields
    double value;

public:
    // Constructor
    DCSource(double value);

    // Functions
    virtual std::complex<double> getValue();
};

#endif // DCSOURCE_HPP
