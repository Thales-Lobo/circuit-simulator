#ifndef ACCURRENTSOURCE_HPP
#define ACCURRENTSOURCE_HPP

#include "sources/AC/ACSource.hpp"

class ACCurrentSource : public ACSource {
public:
    ACCurrentSource(double amplitude, double frequency, double phase);
    ACCurrentSource(std::complex<double> phasor, double frequency);
};

#endif // ACCURRENTSOURCE_HPP
