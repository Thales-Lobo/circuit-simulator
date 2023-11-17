#include "sources/DC/DCCurrentSource.hpp"

// Constructor
DCCurrentSource::DCCurrentSource(double valueParam, Load internalLoadParam)
    : DCSource(valueParam, internalLoadParam) {
        current = value;
    }