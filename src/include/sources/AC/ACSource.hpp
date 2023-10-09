#ifndef ACSOURCE_HPP
#define ACSOURCE_HPP

#include "sources/Source.hpp"

class ACSource : public Source {
protected:
    // Protected fields
    double amplitude;
    double frequency;
    double phase;
    std::complex<double> phasor;

public:
    ACSource(double amplitude, double frequency, double phase);
    ACSource(std::complex<double> phasor, double frequency);
    virtual std::complex<double> getValue();
};

#endif // ACSOURCE_HPP
