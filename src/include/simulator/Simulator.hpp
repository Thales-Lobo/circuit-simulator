#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "Circuit.hpp"
#include <set>

class Simulator {
private:
    Circuit* circuit;
    std::set<Component*> sharedComponents;

    // List all shared components on the circuit
    void computeSharedComponents();
    // Implement logic to check if a component is shared between two meshes
    bool isSharedComponent(Component* component);
    // Implement the logic to obtain the index of the other mesh that shares this component
    int getOtherMeshIndex(Component* component, int currentMeshIndex);

public:
    Simulator(Circuit* circuit);
    void runSimulation();
};

#endif // SIMULATOR_HPP
