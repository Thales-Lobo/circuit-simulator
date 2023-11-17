#ifndef MESH_HPP
#define MESH_HPP

#include <memory>
#include <vector>
#include <unordered_set>
#include "sources/Source.hpp"
#include "load/Load.hpp"
#include "sources/AC/ACCurrentSource.hpp"
#include "sources/AC/ACVoltageSource.hpp"
#include "sources/DC/DCCurrentSource.hpp"
#include "sources/DC/DCVoltageSource.hpp"

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
    std::vector<std::shared_ptr<Source>> sources;   ///< Sources in this mesh
    std::vector<std::shared_ptr<Load>> loads;       ///< Loads in this mesh

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
    Mesh(std::vector<std::shared_ptr<Source>> sources, std::vector<std::shared_ptr<Load>> loads);

    /**
     * @brief Retrieves all loads in the mesh.
     * 
     * @return A vector of pointers to Load objects.
     */
    std::vector<std::shared_ptr<Load>> getLoads() const;

    /**
     * @brief Retrieves all sources in the mesh.
     * 
     * @return A vector of pointers to Source objects.
     */
    std::vector<std::shared_ptr<Source>> getSources() const;

    /**
     * @brief Adds a source to the mesh.
     * 
     * @param source Pointer to the Source object to add.
     */
    void addSource(std::shared_ptr<Source> source);

    /**
     * @brief Adds a load to the mesh.
     * 
     * @param load Pointer to the Load object to add.
     */
    void addLoad(std::shared_ptr<Load> load);

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
    std::vector<std::shared_ptr<Load>> commonLoads(const Mesh* otherMesh) const;
};

#endif // MESH_HPP
