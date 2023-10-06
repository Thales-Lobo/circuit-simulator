#ifndef SOURCE_HPP
#define SOURCE_HPP

#include <complex>

class Source {
public:
    // Returns the source value
    virtual std::complex<double> getValue() = 0; 
};

#endif // SOURCE_HPP
