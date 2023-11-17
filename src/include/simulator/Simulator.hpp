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
    std::set<std::shared_ptr<Load>> sharedLoads;

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
    bool isSharedLoad(const std::shared_ptr<Load>& load) const;

    /**
     * @brief Finds the index of another mesh that shares the given load.
     *
     * @param load Pointer to the load for which the other mesh index is required.
     * @param currentMeshIndex The index of the current mesh to be excluded from the search.
     * @return The index of another mesh that shares the load, if any.
     */
    size_t getOtherMeshIndex(const std::shared_ptr<Load>& load, size_t currentMeshIndex) const;

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

    /**
     * @brief Assigns the calculated mesh current to each load in a given mesh.
     * 
     * This function iterates over all the loads in the specified mesh and assigns
     * the current to them. It handles shared and non-shared loads appropriately by
     * invoking `determineLoadCurrent`.
     * 
     * @param mesh Pointer to the Mesh object containing the loads.
     * @param meshCurrent The calculated current for the mesh.
     * @param meshIndex Index of the mesh in the simulation.
     */
    void assignCurrentToLoads(Mesh* mesh, const std::complex<double>& meshCurrent, size_t meshIndex);

    /**
     * @brief Determines the current for a given load, considering shared loads.
     * 
     * For shared loads (loads that are part of multiple meshes), this function
     * calculates the net current by considering the currents in all the meshes it
     * belongs to. For non-shared loads, it simply returns the mesh current.
     * 
     * @param load Pointer to the Load object.
     * @param meshCurrent The calculated current for the mesh containing the load.
     * @param meshIndex Index of the mesh in the simulation.
     * @return std::complex<double> The determined current for the load.
     */
    std::complex<double> determineLoadCurrent(const std::shared_ptr<Load>& load, const std::complex<double>& meshCurrent, size_t meshIndex);

    /**
     * @brief Assigns the mesh current to each voltage source within a mesh.
     * 
     * This function iterates over all the sources in the specified mesh. It checks
     * if the source is an AC or DC voltage source and assigns the mesh current to it.
     * This ensures that the voltage sources in the circuit simulation are correctly
     * influenced by the mesh currents.
     * 
     * @param mesh Pointer to the Mesh object containing the voltage sources.
     * @param meshCurrent The calculated current for the mesh.
     */
    void assignCurrentToVoltageSources(Mesh* mesh, const std::complex<double>& meshCurrent);
};

#endif // SIMULATOR_HPP
