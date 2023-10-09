#include "load/components/Component.hpp"

// Constructor
Component::Component(){};

Component::Component(double componentValue, double angularFrequency) {
    this->componentValue    = componentValue;
    this->angularFrequency  = angularFrequency;
}

// Getters
double Component::getComponentValue() {
    return componentValue;
}

double Component::getAngularFrequency() {
    return angularFrequency;
}

// Setters
void Component::setComponentValue(double componentValue) {
    this->componentValue = componentValue;
}

void Component::setAngularFrequency(double angularFrequency) {
    this->angularFrequency = angularFrequency;
}
