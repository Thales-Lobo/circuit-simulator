#ifndef LOAD_HPP
#define LOAD_HPP

#include "constants/Constants.hpp"
#include <complex>

/**
 * @file Load.hpp
 *
 * The Load class represents an electrical load within a circuit.
 * It encapsulates the properties of the load such as impedance,
 * voltage, current, and power, and provides methods to access and
 * manipulate these properties.
 */

class Load {
protected:
    /**
     * @enum RepresentationMode
     * 
     * The RepresentationMode enum specifies the format in which
     * complex numbers are represented. This is used when initializing
     * a Load object with values that represent its impedance.
     */
    enum class RepresentationMode {
        RECTANGULAR,    ///< Represents complex numbers in rectangular form (real + imaginary).
        POLAR_DEGREES,  ///< Represents complex numbers in polar form with angle in degrees.
        POLAR_RADIANS   ///< Represents complex numbers in polar form with angle in radians.
    };

    // Protected fields
    std::complex<double> impedance; ///< The complex impedance of the load.
    std::complex<double> voltage;   ///< The complex voltage across the load.
    std::complex<double> current;   ///< The complex current through the load.
    std::complex<double> complexPower; ///< The complex power consumed by the load.
    double activePower;             ///< The active (real) power consumed by the load.
    double reactivePower;           ///< The reactive power consumed by the load.
    double phase;                   ///< The phase angle of the load (in radians).

    // Protected functions
    void calculateVoltage();        ///< Calculates the voltage across the load based on current and impedance.
    void calculatePowers();         ///< Calculates the powers (active, reactive, complex) of the load.

public:
    // Constructors
    Load(); ///< Default constructor that initializes a Load object with default values.
    /**
     * @brief Parameterized constructor for Load class.
     * 
     * @param firstValue The real part of the impedance if in RECTANGULAR mode, or the magnitude if in POLAR modes.
     * @param secondValue The imaginary part of the impedance if in RECTANGULAR mode, or the phase angle if in POLAR modes.
     * @param mode The representation mode of the given values (default is POLAR_DEGREES).
     */
    Load(double firstValue, double secondValue, RepresentationMode mode = RepresentationMode::POLAR_DEGREES);

    // Destructors
    virtual ~Load() = default; ///< Default virtual destructor.
    
    // Getters
    std::complex<double> getImpedance() const; ///< Returns the complex impedance of the load.
    std::complex<double> getVoltage() const;   ///< Returns the complex voltage across the load.
    std::complex<double> getCurrent() const;   ///< Returns the complex current through the load.
    std::complex<double> getComplexPower() const; ///< Returns the complex power consumed by the load.
    double getActivePower() const;             ///< Returns the active power consumed by the load.
    double getReactivePower() const;           ///< Returns the reactive power consumed by the load.
    double getPhase() const;                   ///< Returns the phase angle of the load.
    
    // Setters
    /**
     * @brief Sets the current through the load.
     * 
     * @param current The complex current to be set for the load.
     */
    void setCurrent(std::complex<double> current);
};

#endif // LOAD_HPP
