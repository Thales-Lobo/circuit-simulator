#include "sources/DC/DCSource.hpp"

// Constructor
DCSource::DCSource(double value) {
    this->value = value;
}

std::complex<double> DCSource::getValue() {
    return std::complex<double>(this->value, 0.0);
}
