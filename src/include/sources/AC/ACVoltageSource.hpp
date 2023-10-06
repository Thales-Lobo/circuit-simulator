#ifndef ACVOLTAGESOURCE_HPP
#define ACVOLTAGESOURCE_HPP

#include "ACSource.hpp"

class ACVoltageSource : public ACSource {
public:
    ACVoltageSource(double amplitude, double frequency, double phase)
        : ACSource(amplitude, frequency, phase) {}
    ACVoltageSource(std::complex<double> phasor, double frequency)
        : ACSource(phasor, frequency) {}      
};

#endif // ACVOLTAGESOURCE_HPP
