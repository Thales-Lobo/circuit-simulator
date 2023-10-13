#include "load/components/Component.hpp"

// Default constructor
Component::Component() = default;

// Constructor using component value and angular frequency
Component::Component(double componentValue, double angularFrequency)
    : componentValue(componentValue), angularFrequency(angularFrequency) {
    
    if (angularFrequency == 0.0) {
        throw std::runtime_error("Angular frequency cannot be zero!");
    }

    if (componentValue == 0.0) {
        throw std::runtime_error("Component value cannot be zero!");
    }
}

// Getters
double Component::getComponentValue() const {
    return componentValue;
}

double Component::getAngularFrequency() const {
    return angularFrequency;
}

// Setters
void Component::setComponentValue(double newComponentValue) {
    componentValue = newComponentValue;
}

void Component::setAngularFrequency(double newAngularFrequency) {
    angularFrequency = newAngularFrequency;
}
