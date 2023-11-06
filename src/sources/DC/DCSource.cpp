#include "sources/DC/DCSource.hpp"

// Constructor
DCSource::DCSource(double value, Load internalLoad) {
    value = value;
    internalLoad = internalLoad;
}

std::complex<double> DCSource::getValue() {
    return std::complex<double>(value, 0.0);
}
