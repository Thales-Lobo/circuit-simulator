#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include "circuit/Mesh.hpp"
#include "sources/AC/ACCurrentSource.hpp"
#include "sources/DC/DCCurrentSource.hpp"
#include <Eigen/Dense>
#include <vector>
#include <complex>
#include <unordered_map>
#include <memory>

/**
 * @brief Represents an electrical circuit composed of multiple meshes.
 * 
 * The Circuit class encapsulates the functionality to manage the collection of meshes
 * that make up an electrical circuit, and provides the capability to solve for the mesh
 * currents using matrix methods. It leverages the Eigen library for complex number and
 * matrix operations, facilitating the analysis of the circuit.
 */
class Circuit {
private:
    using CurrentSourceMap = std::unordered_map<CurrentSource*, std::vector<size_t>>;

    std::vector<std::unique_ptr<Mesh>> meshes;  ///< Stores unique pointers to Mesh objects within the circuit.
    std::vector<std::complex<double>> meshCurrents; ///< Holds the currents for each mesh as complex numbers, post-solution.
    Eigen::MatrixXcd impedanceMatrix; ///< Represents the impedance relationships between meshes as a complex matrix.
    Eigen::VectorXcd voltageVector; ///< Captures the net voltage for each mesh as a complex vector.
    Eigen::VectorXcd currentVector; ///< Contains the solution for mesh currents as a complex vector.

    // Private helper methods for circuit analysis
    CurrentSourceMap mapCurrentSourcesToMeshes() const; ///< Maps current sources to the meshes they influence, essential for setting up the circuit equations
    std::complex<double> calculateCommonImpedance(const Mesh* mesh1, const Mesh* mesh2) const;  ///< Calculates the impedance common to two meshes, used in constructing the impedance matrix
    void prepareImpedanceMatrix(size_t numMeshes, size_t matrixSize, const CurrentSourceMap& currentSourcesMap);    ///< Sets up the impedance matrix, accounting for the impedance of each mesh and the influence of current sources
    void fillImpedanceMatrixRow(size_t row, const Mesh* mesh);  ///< Populates a single row of the impedance matrix with the impedance values of a given mesh
    void addCurrentSourcesToImpedanceMatrix(size_t numMeshes, const CurrentSourceMap& currentSourcesMap);   ///< Integrates current sources into the impedance matrix, modifying it to reflect their presence
    void addCurrentSourceBetweenMeshes(size_t row, const std::vector<size_t>& meshIndices); ///< Inserts the effects of a current source that spans two meshes into the impedance matrix
    void prepareVoltageVector(size_t numMeshes, size_t matrixSize);  ///< Prepares the voltage vector for the circuit, which includes the voltages of meshes and the effects of current sources
    void solveSystemOfEquations(); ///< Solves the matrix equation to find the mesh currents, using the impedance matrix and voltage vector
    void assignCurrentsToSources(size_t numMeshes, const CurrentSourceMap& currentSourcesMap);  ///<

public:
    // Constructors
    /**
     * @brief Default constructor that initializes an empty circuit.
     */
    Circuit();

    /**
     * @brief Constructs a circuit with a given collection of meshes.
     * @param meshes Vector of unique pointers to Mesh objects.
     */
    Circuit(std::vector<std::unique_ptr<Mesh>> meshes);

    // Mesh management methods
    /**
     * @brief Adds a mesh to the circuit.
     * @param mesh Unique pointer to the Mesh object to be added to the circuit.
     */
    void addMesh(std::unique_ptr<Mesh> mesh);

    /**
     * @brief Retrieves pointers to all the Mesh objects in the circuit.
     * @return Vector of raw pointers to Mesh objects.
     */
    std::vector<Mesh*> getMeshes() const;

    // Getters for circuit properties
    /**
     * @brief Gets the currents for each mesh in the circuit.
     * @return Vector of complex numbers representing the mesh currents.
     */
    std::vector<std::complex<double>> getMeshCurrents() const;

    /**
     * @brief Gets the impedance matrix of the circuit.
     * @return Constant reference to the impedance matrix.
     */
    const Eigen::MatrixXcd& getImpedanceMatrix() const;

    /**
     * @brief Gets the voltage vector for the circuit.
     * @return Constant reference to the voltage vector.
     */
    const Eigen::VectorXcd& getVoltageVector() const;

    /**
     * @brief Gets the current vector representing the solution for mesh currents.
     * @return Constant reference to the current vector.
     */
    const Eigen::VectorXcd& getCurrentVector() const;

    // Circuit analysis method
    /**
     * @brief Solves for the mesh currents in the circuit using matrix methods.
     * 
     * This method sets up and solves the system of equations derived from the circuit's
     * mesh analysis. It updates the meshCurrents vector with the solution.
     */
    void solveMeshCurrents();
};

#endif // CIRCUIT_HPP
