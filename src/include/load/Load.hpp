#ifndef LOAD_HPP
#define LOAD_HPP

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
    
    // Getters
    std::complex<double> getImpedance();
    std::complex<double> getVoltage();
    std::complex<double> getCurrent();
    std::complex<double> getComplexPower();
    double getActivePower();
    double getReactivePower();
    double getPhase();
    
    // Setters
    void setVoltage(std::complex<double> voltage);
    void setCurrent(std::complex<double> current);
    void setComplexPower(std::complex<double> complexPower);
    void setActivePower(double activePower);
    void setReactivePower(double reactivePower);
    void setPhase(double phase);
};

#endif // LOAD_HPP
