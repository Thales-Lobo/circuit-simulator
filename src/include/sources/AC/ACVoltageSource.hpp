#ifndef ACVOLTAGESOURCE_HPP
#define ACVOLTAGESOURCE_HPP

#include "sources/AC/ACSource.hpp"

class ACVoltageSource : public ACSource {
public:
    ACVoltageSource(double amplitude, double frequency, double phase);
    ACVoltageSource(std::complex<double> phasor, double frequency); 
};

#endif // ACVOLTAGESOURCE_HPP
