#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <complex>

class Component {
protected:
    // Protected class
    enum class ComponentMode {
        VALUE_FREQUENCY,
        RECTANGULAR,
        POLAR_DEGREES,
        POLAR_RADIANS
    };

    // Protected fields
    double componentValue;
    double angularFrequency;
    std::complex<double> impedance; 
    std::complex<double> voltage; 
    std::complex<double> current;
    std::complex<double> complexPower;
    double activePower;
    double reactivePower;
    double phase;

    // Protected functions
    virtual void calculateImpedance();
    virtual void calculateComponentValue();
    void calculateVoltage();
    void calculatePowers();

public:
    // Constructors
    Component(double firstValue, double secondValue, ComponentMode mode);
    
    // Getters
    double getComponentValue();
    double getAngularFrequency();
    std::complex<double> getImpedance();
    std::complex<double> getVoltage();
    std::complex<double> getCurrent();
    std::complex<double> getComplexPower();
    double getActivePower();
    double getReactivePower();
    double getPhase();
    
    // Setters
    void setComponentValue(double componentValue);
    void setAngularFrequency(double angularFrequency);
    void setVoltage(std::complex<double> voltage);
    void setCurrent(std::complex<double> current);
    void setComplexPower(std::complex<double> complexPower);
    void setActivePower(double activePower);
    void setReactivePower(double reactivePower);
    void setPhase(double phase);
};

#endif // COMPONENT_HPP
