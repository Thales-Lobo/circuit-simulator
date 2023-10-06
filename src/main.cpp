#include "ACVoltageSource.hpp"
#include "Resistor.hpp"
#include "Inductor.hpp"
#include "Mesh.hpp"
#include "Circuit.hpp"
#include "Simulator.hpp"
#include <iostream>
#include <vector>

int main() {
    // Creating components
    ACVoltageSource* voltageSource  = new ACVoltageSource(100.0, 60.0, 0.0); // 10V, 60Hz, 0 graus
    Resistor* resistorA             = new Resistor(20.0, 0); // 200 ohms
    Resistor* resistorB             = new Resistor(30.0, 0); // 300 ohms

    // Creating a mesh with the components
    std::vector<Source*> sources        = {voltageSource};
    std::vector<Component*> components  = {resistorA, resistorB};
    Mesh* mesh = new Mesh(sources, components);

    // Creating a circuit with the mesh
    std::vector<Mesh*> meshes   = {mesh};
    Circuit* circuit            = new Circuit(meshes);

    // Simulating the circuit
    Simulator simulator(circuit);
    simulator.runSimulation();

    // Printing eletric properties
    std::cout << "Mesh Current: "               << circuit->getMeshCurrents()[0]    << " A" << std::endl;
    std::cout << "ResistorA Voltage: "          << resistorA->getVoltage()          << " V" << std::endl;
    std::cout << "ResistorA Complex Power: "    << resistorA->getComplexPower()     << " VA" << std::endl;

    // Clean memory
    delete voltageSource;
    delete resistorA;
    delete resistorB;
    delete mesh;
    delete circuit;

    return 0;
}
