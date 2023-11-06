#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include "circuit/Mesh.hpp"
#include "sources/AC/ACCurrentSource.hpp"
#include "sources/DC/DCCurrentSource.hpp"
#include <Eigen/Dense>
#include <vector>
#include <complex>
#include <unordered_map>

/**
 * @brief The Circuit class represents an electrical circuit composed of meshes.
 * 
 * This class is responsible for managing the meshes within a circuit, adding meshes,
 * and solving for the mesh currents using matrix methods. It utilizes the Eigen library
 * for handling complex numbers and matrix operations.
 */
class Circuit {
private:
    std::vector<Mesh*> meshes;  ///< Vector of pointers to Mesh objects in the circuit.
    std::vector<std::complex<double>> meshCurrents; ///< Vector of complex numbers representing the currents in each mesh.
    Eigen::MatrixXcd impedanceMatrix; ///< Matrix of complex numbers representing the impedance between meshes.
    Eigen::VectorXcd voltageVector; ///< Vector of complex numbers representing the voltage for each mesh.
    Eigen::VectorXcd currentVector; ///< Vector of complex numbers representing the solution for mesh currents.

public:
    /**
     * @brief Default constructor for the Circuit class.
     * 
     * Initializes an empty circuit with no meshes.
     */
    Circuit();

    /**
     * @brief Parameterized constructor for the Circuit class.
     * 
     * Initializes a circuit with a given vector of meshes.
     * @param meshes Vector of pointers to Mesh objects to be included in the circuit.
     */
    Circuit(std::vector<Mesh*> meshes);

    /**
     * @brief Adds a mesh to the circuit.
     * 
     * This function takes a pointer to a Mesh object and adds it to the circuit's list of meshes.
     * @param mesh Pointer to the Mesh object to add.
     */
    void addMesh(Mesh* mesh);

    /**
     * @brief Retrieves all meshes in the circuit.
     * 
     * This function returns a vector containing pointers to all the Mesh objects in the circuit.
     * @return Vector of pointers to Mesh objects.
     */
    std::vector<Mesh*> getMeshes() const;

    /**
     * @brief Retrieves the mesh currents.
     * 
     * This function returns a vector of complex numbers representing the currents in each mesh after the circuit has been solved.
     * @return Vector of complex numbers representing the mesh currents.
     */
    std::vector<std::complex<double>> getMeshCurrents() const;

    /**
     * @brief Retrieves the impedance matrix of the circuit.
     * 
     * This function returns a constant reference to the impedance matrix of the circuit, which represents the impedance between each pair of meshes.
     * @return Constant reference to the impedance matrix.
     */
    const Eigen::MatrixXcd& getImpedanceMatrix() const;

    /**
     * @brief Retrieves the voltage vector of the circuit.
     * 
     * This function returns a constant reference to the voltage vector of the circuit, which represents the net voltage for each mesh.
     * @return Constant reference to the voltage vector.
     */
    const Eigen::VectorXcd& getVoltageVector() const;
    
    /**
     * @brief Retrieves the current vector of the circuit.
     * 
     * This function returns a constant reference to the current vector of the circuit, which represents the calculated mesh currents after solving the circuit.
     * @return Constant reference to the current vector.
     */
    const Eigen::VectorXcd& getCurrentVector() const;

    /**
     * @brief Analyzes and maps current sources to their respective meshes.
     * 
     * This function identifies which current sources are present in multiple meshes and creates a mapping from each current source to the meshes it is part of.
     * @return Unordered map with current sources as keys and vectors of integers representing the indices of meshes as values.
     */
    std::unordered_map<CurrentSource*, std::vector<size_t>> mapCurrentSourcesToMeshes() const;

    /**
     * @brief Solves for the mesh currents using matrix methods.
     * 
     * This function applies matrix methods to solve for the currents in each mesh of the circuit. It uses the Eigen library to perform matrix operations.
     */
    void solveMeshCurrents();
};

#endif // CIRCUIT_HPP
