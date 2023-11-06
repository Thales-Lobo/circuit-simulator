#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "circuit/Circuit.hpp"
#include <set>
#include <unordered_map>

class Simulator {
private:
    Circuit* circuit;
    std::set<Load*> sharedLoads;

    // List all shared loads on the circuit
    void computeSharedLoads();
    // Implement logic to check if a load is shared between two meshes
    bool isSharedLoad(Load* load) const;
    // Implement the logic to obtain the index of the other mesh that shares this load
    int getOtherMeshIndex(Load* load, int currentMeshIndex) const;

public:
    Simulator(Circuit* circuit);
    void runSimulation();
};

#endif // SIMULATOR_HPP
