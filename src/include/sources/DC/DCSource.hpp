#ifndef DCSOURCE_HPP
#define DCSOURCE_HPP

#include "sources/Source.hpp"
#include <complex>

/**
 * @file DCSource.hpp
 *
 * Declares the DCSource class, which is a base class for all direct current (DC) sources.
 * It inherits from the Source class and provides the basic interface and common functionality
 * for DC sources in an electrical circuit simulation.
 */

class DCSource : virtual public Source {
protected:
    /**
     * @brief The magnitude of the DC source value.
     *
     * This could represent either voltage or current, depending on the specific type of DC source.
     * The value is stored as a double-precision floating-point number.
     */
    double value;

public:
    /**
     * @brief Constructs a DC source with a specified value and an optional internal load.
     *
     * The constructor initializes a DC source with the given value. The internal load can be
     * specified if the source has an inherent impedance; otherwise, it defaults to an ideal source
     * with zero internal impedance.
     *
     * @param value The magnitude of the DC source (voltage or current).
     * @param internalLoad The internal load of the source, defaulting to an impedance of 0.0.
     */
    DCSource(double value, Load internalLoad = Load(0.0, 0.0, Load::RepresentationMode::POLAR_DEGREES));

    /**
     * @brief Virtual destructor for the DCSource class.
     *
     * Ensures that derived class destructors are called correctly when deleting instances of a derived class
     * through a pointer to DCSource. This destructor is defaulted.
     */
    virtual ~DCSource() override = default;

    /**
     * @brief Retrieves the value of the DC source.
     *
     * This function is virtual and should be overridden by derived classes to return the specific
     * value of the DC source they represent. The value is returned as a complex number, where the
     * real part represents the magnitude and the imaginary part is typically zero for DC sources.
     *
     * @return std::complex<double> The complex representation of the DC source's value.
     */
    virtual std::complex<double> getValue();
};

#endif // DCSOURCE_HPP
