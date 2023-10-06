#ifndef ACCURRENTSOURCE_HPP
#define ACCURRENTSOURCE_HPP

#include "ACSource.hpp"

class ACCurrentSource : public ACSource {
public:
    ACCurrentSource(double amplitude, double frequency, double phase)
        : ACSource(amplitude, frequency, phase) {}
    ACCurrentSource(std::complex<double> phasor, double frequency)
        : ACSource(phasor, frequency) {}

};

#endif // ACCURRENTSOURCE_HPP
