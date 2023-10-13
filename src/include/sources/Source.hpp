#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "constants/Constants.hpp"
#include <complex>

class Source {
public:
    // Returns the source value
    virtual std::complex<double> getValue() = 0;

    // Destructors
    virtual ~Source() = default;
};

#endif // SOURCE_HPP
