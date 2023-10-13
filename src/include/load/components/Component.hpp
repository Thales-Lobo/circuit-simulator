#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "load/Load.hpp"

class Component : public Load {
protected:
    // Protected fields
    double componentValue;
    double angularFrequency;

public:
    // Constructors
    Component();
    Component(double componentValue, double angularFrequency);
    
    // Getters
    double getComponentValue() const;
    double getAngularFrequency() const;
    
    // Setters
    void setComponentValue(double componentValue);
    void setAngularFrequency(double angularFrequency);
};

#endif // COMPONENT_HPP
