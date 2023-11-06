// Sources includes
#include "sources/DC/DCVoltageSource.hpp"
#include "sources/DC/DCCurrentSource.hpp"
#include "sources/AC/ACVoltageSource.hpp"
#include "sources/AC/ACCurrentSource.hpp"
// Loads includes
#include "load/Load.hpp"
#include "load/components/Resistor.hpp"
#include "load/components/Inductor.hpp"
#include "load/components/Capacitor.hpp"
// Circuits includes
#include "circuit/Mesh.hpp"
#include "circuit/Circuit.hpp"
#include "simulator/Simulator.hpp"
// General C++ includes
#include <iostream>
#include <vector>
#include <complex>

int main() {
    // Creating voltage sources
    ACVoltageSource* voltageSource1  = new ACVoltageSource(60.0, 20.0 , 60.0); // 50V, 20°, 60Hz
    ACVoltageSource* voltageSource2  = new ACVoltageSource(-10.0, 70.0, 60.0); // -10V, 70°, 60Hz

    // Creating loads
    Load* load1 = new Load(30.0, 30.0); // 30/_30° ohms
    Load* load2 = new Load(40.0, 60.0); // 40/_60° ohms
    Load* load3 = new Load(15.0, 20.0); // 15/_50° ohms

    // Creating the first mesh with the loads
    std::vector<Source*> sources1   = {voltageSource1};
    std::vector<Load*> loads1       = {load1};
    Mesh* mesh1                     = new Mesh(sources1, loads1);

    // Creating a circuit with the mesh
    std::vector<Mesh*> meshes   = {mesh1};
    Circuit* circuit            = new Circuit(meshes);

    // Simulating the circuit
    Simulator simulator(circuit);
    simulator.runSimulation();

    // Printing eletric properties
    std::cout << "Mesh 1 Current : "           << std::abs(circuit->getMeshCurrents()[0])  << "/_" << (180.0 / std::acos(-1)) * std::arg(circuit->getMeshCurrents()[0])    << " A" << std::endl;
    //std::cout << "Mesh 2 Current : "           << std::abs(circuit->getMeshCurrents()[1])  << "/_" << (180.0 / std::acos(-1)) * std::arg(circuit->getMeshCurrents()[1])    << " A" << std::endl;

    // Clean memory
    delete voltageSource1;
    delete voltageSource2;
    delete load1;
    delete load2;
    delete load3;
    delete mesh1;
    //delete mesh2;
    delete circuit;

    return 0;
}
