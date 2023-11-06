#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "constants/Constants.hpp"
#include "Load/Load.hpp"
#include <complex>

/**
 * @file Source.hpp
 *
 * Declares the Source class, which serves as a base class for different types of sources
 * in an electrical circuit simulation, such as voltage or current sources.
 */

class Source {
protected:
    Load internalLoad; ///< Internal load associated with the source.
    std::complex<double> voltage; ///< Complex voltage across the source.
    std::complex<double> current; ///< Complex current through the source.
    std::complex<double> complexPower; ///< Complex power delivered by the source.
    double activePower; ///< Active (real) power delivered by the source.
    double reactivePower; ///< Reactive (imaginary) power delivered by the source.
    double phase; ///< Phase angle of the source.

public:
    /**
     * @brief Virtual destructor for the Source class.
     *
     * Being a pure virtual function, it makes Source an abstract class that cannot be instantiated.
     * It ensures that the destructor of derived classes is called.
     */
    virtual ~Source() = 0;

    /**
     * @brief Calculates the powers associated with the source.
     *
     * This function computes the complex, active, and reactive power based on the
     * voltage and current of the source.
     */
    void calculatePowers();

    /**
     * @brief Gets the internal load of the source.
     *
     * @return The complex impedance of the internal load.
     */
    std::complex<double> getInternalLoad() const;

    /**
     * @brief Gets the voltage of the source.
     *
     * @return The complex voltage across the source.
     */
    std::complex<double> getVoltage() const;

    /**
     * @brief Gets the current through the source.
     *
     * @return The complex current through the source.
     */
    std::complex<double> getCurrent() const;

    /**
     * @brief Gets the complex power of the source.
     *
     * @return The complex power delivered by the source.
     */
    std::complex<double> getComplexPower() const;

    /**
     * @brief Gets the active power of the source.
     *
     * @return The active (real) power delivered by the source.
     */
    double getActivePower() const;

    /**
     * @brief Gets the reactive power of the source.
     *
     * @return The reactive (imaginary) power delivered by the source.
     */
    double getReactivePower() const;

    /**
     * @brief Gets the phase angle of the source.
     *
     * @return The phase angle in radians.
     */
    double getPhase() const;
};

#endif // SOURCE_HPP
