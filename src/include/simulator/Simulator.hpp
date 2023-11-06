#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "circuit/Circuit.hpp"
#include <set>
#include <unordered_map>

/**
 * @file Simulator.hpp
 *
 * The Simulator class is responsible for running simulations on an electrical circuit.
 * It uses the Circuit class to represent the circuit being simulated and contains
 * methods to identify shared loads and run the simulation logic.
 */

class Simulator {
private:
    /**
     * @brief Pointer to the circuit to be simulated.
     */
    Circuit* circuit;

    /**
     * @brief Set of loads that are shared between different meshes in the circuit.
     */
    std::set<Load*> sharedLoads;

    /**
     * @brief Computes all the shared loads within the circuit.
     *
     * This method populates the sharedLoads set with loads that are common
     * between two or more meshes in the circuit.
     */
    void computeSharedLoads();

    /**
     * @brief Checks if a load is shared between two or more meshes.
     *
     * @param load Pointer to the load to be checked.
     * @return True if the load is shared, false otherwise.
     */
    bool isSharedLoad(Load* load) const;

    /**
     * @brief Finds the index of another mesh that shares the given load.
     *
     * @param load Pointer to the load for which the other mesh index is required.
     * @param currentMeshIndex The index of the current mesh to be excluded from the search.
     * @return The index of another mesh that shares the load, if any.
     */
    size_t getOtherMeshIndex(Load* load, size_t currentMeshIndex) const;

public:
    /**
     * @brief Constructor for the Simulator class.
     *
     * Initializes a new instance of the Simulator class with a given circuit.
     *
     * @param circuit Pointer to the circuit to be simulated.
     */
    Simulator(Circuit* circuit);

    /**
     * @brief Runs the simulation on the circuit.
     *
     * This method executes the simulation logic, which includes computing shared loads,
     * applying simulation algorithms, and updating the circuit state.
     */
    void runSimulation();
};

#endif // SIMULATOR_HPP
