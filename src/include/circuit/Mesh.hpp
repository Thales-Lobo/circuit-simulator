#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <complex>
#include "sources/Source.hpp"
#include "sources/VoltageSource.hpp"
#include "sources/CurrentSource.hpp"
#include "load/Load.hpp"

/**
 * @brief The Mesh class represents an electrical circuit mesh.
 * 
 * A mesh is a loop that does not contain any other loops within it.
 * This class manages the sources and loads within a single mesh and
 * provides methods to calculate the total voltage, impedance, and
 * to retrieve the sources and loads.
 */
class Mesh {
private:
    std::vector<Source*> sources; ///< Sources in this mesh
    std::vector<Load*> loads;     ///< Loads in this mesh

public:
    /**
     * @brief Default constructor for Mesh.
     * 
     * Initializes an empty mesh with no sources or loads.
     */
    Mesh();

    /**
     * @brief Parameterized constructor for Mesh.
     * 
     * Initializes a mesh with the given sources and loads.
     * 
     * @param sources Vector of pointers to Source objects.
     * @param loads Vector of pointers to Load objects.
     */
    Mesh(std::vector<Source*> sources, std::vector<Load*> loads);

    /**
     * @brief Retrieves all loads in the mesh.
     * 
     * @return A vector of pointers to Load objects.
     */
    std::vector<Load*> getLoads() const;

    /**
     * @brief Retrieves all sources in the mesh.
     * 
     * @return A vector of pointers to Source objects.
     */
    std::vector<Source*> getSources() const;

    /**
     * @brief Adds a source to the mesh.
     * 
     * @param source Pointer to the Source object to add.
     */
    void addSource(Source* source);

    /**
     * @brief Adds a load to the mesh.
     * 
     * @param load Pointer to the Load object to add.
     */
    void addLoad(Load* load);

    /**
     * @brief Calculates the total voltage of the mesh.
     * 
     * @return The total voltage as a complex number.
     */
    std::complex<double> calculateMeshVoltage() const;

    /**
     * @brief Calculates the total impedance of the mesh.
     * 
     * @return The total impedance as a complex number.
     */
    std::complex<double> calculateMeshImpedance() const;

    /**
     * @brief Finds common loads between this mesh and another mesh.
     * 
     * @param otherMesh Pointer to another Mesh object.
     * @return A vector of pointers to Load objects that are common between the two meshes.
     */
    std::vector<Load*> commonLoads(const Mesh* otherMesh) const;
};

#endif // MESH_HPP
