#ifndef LOAD_HPP
#define LOAD_HPP

#include "constants/Constants.hpp"
#include <complex>

class Load {
protected:
    // Protected classes
    enum class RepresentationMode {
        RECTANGULAR,
        POLAR_DEGREES,
        POLAR_RADIANS
    };

    // Protected fields
    std::complex<double> impedance; 
    std::complex<double> voltage; 
    std::complex<double> current;
    std::complex<double> complexPower;
    double activePower;
    double reactivePower;
    double phase;

    // Protected functions
    void calculateVoltage();
    void calculatePowers();

public:
    // Constructors
    Load();
    Load(double firstValue, double secondValue, RepresentationMode mode = RepresentationMode::POLAR_DEGREES);

    // Destructors
    virtual ~Load() = default;
    
    // Getters
    std::complex<double> getImpedance() const;
    std::complex<double> getVoltage() const;
    std::complex<double> getCurrent() const;
    std::complex<double> getComplexPower() const;
    double getActivePower() const;
    double getReactivePower() const;
    double getPhase() const;
    
    // Setters
    void setCurrent(std::complex<double> current);
};

#endif // LOAD_HPP
