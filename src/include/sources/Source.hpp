#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "load/Load.hpp"
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

    /**
     * @brief Set the Internal Load of the Source.
     *
     * This method sets the internal load of the Source object. The internal load
     * can be any value of the Load type, and it represents a specific load
     * characteristic or requirement of the Source. This setting might affect
     * how the Source interacts with connected circuits or components.
     *
     * @param internalLoadParam The internal load value to be set for the Source.
     *                          This parameter must be of Load type and represents the
     *                          load characteristic to be applied to the Source.
     */
    void setInternalLoad(Load internalLoadParam);

    /**
     * @brief Sets the voltage of the source.
     *
     * This function allows setting the complex voltage across the source. It updates the voltage
     * member variable to the specified value.
     *
     * @param voltage The complex voltage to be set for the source.
     */
    void setVoltage(std::complex<double> voltage);

    /**
     * @brief Sets the current through the source.
     *
     * This function enables setting the complex current through the source. It updates the current
     * member variable with the provided value.
     *
     * @param current The complex current to be set for the source.
     */
    void setCurrent(std::complex<double> current);
};

#endif // SOURCE_HPP
