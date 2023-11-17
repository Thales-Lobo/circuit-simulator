#include "sources/DC/DCSource.hpp"

// Constructor
DCSource::DCSource(double valueParam, Load internalLoadParam) {
    value = valueParam;
    internalLoad = internalLoadParam;
}

std::complex<double> DCSource::getValue() {
    return std::complex<double>(value, 0.0);
}
