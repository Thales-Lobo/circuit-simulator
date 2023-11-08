// Constants includes
#include "constants/Constants.hpp"

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

// Function prototypes for creating components
ACVoltageSource* createACVoltageSource(double magnitude, double phase, double frequency);
Load* createLoad(double magnitude, double phase);
Mesh* createMesh(const std::vector<Source*>& sources, const std::vector<Load*>& loads);
Circuit* createCircuit(const std::vector<Mesh*>& meshes);
void printMatrix(const Eigen::MatrixXcd& matrix);
void printVector(const Eigen::VectorXcd& vector);

// Function definitions for creating components
// Creates an AC voltage source
ACVoltageSource* createACVoltageSource(double magnitude, double phase, double frequency) {
    return new ACVoltageSource(magnitude, phase, frequency);
}

// Creates a load with specified magnitude and phase
Load* createLoad(double magnitude, double phase) {
    return new Load(magnitude, phase);
}

// Creates a mesh from given sources and loads
Mesh* createMesh(const std::vector<Source*>& sources, const std::vector<Load*>& loads) {
    return new Mesh(sources, loads);
}

// Creates a circuit from a collection of meshes
Circuit* createCircuit(const std::vector<Mesh*>& meshes) {
    return new Circuit(meshes);
}

// Prints a matrix to the console
void printMatrix(const Eigen::MatrixXcd& matrix) {
    for (int row = 0; row < matrix.rows(); ++row) {
        for (int column = 0; column < matrix.cols(); ++column) {
            std::complex<double> val = matrix(row, column);
            std::cout << "(" << val.real();
            if (val.imag() >= 0) std::cout << "+";
            std::cout << val.imag() << "i) ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Prints a vector to the console
void printVector(const Eigen::VectorXcd& vector) {
    for (int index = 0; index < vector.size(); ++index) {
        std::complex<double> val = vector(index);
        std::cout << "(" << val.real();
        if (val.imag() >= 0) std::cout << "+";
        std::cout << val.imag() << "i) ";
    }
    std::cout << std::endl;
}

int main() {
    // Create voltage sources
    ACVoltageSource* voltageSource1 = createACVoltageSource(60.0, 20.0, 60.0); // 60V, 20°, 60Hz
    ACVoltageSource* voltageSource2 = createACVoltageSource(-10.0, 70.0, 60.0); // -10V, 70°, 60Hz

    // Create loads
    Load* load1 = createLoad(30.0, 30.0); // 30 ohms at 30°
    Load* load2 = createLoad(40.0, 60.0); // 40 ohms at 60°
    Load* load3 = createLoad(15.0, 20.0); // 15 ohms at 20°

    // Create the first mesh with the loads
    std::vector<Source*> sources1 = {voltageSource1};
    std::vector<Load*> loads1 = {load1, load3};

    // Create the second mesh with the loads
    std::vector<Source*> sources2 = {voltageSource2};
    std::vector<Load*> loads2 = {load3, load2};

    // Create meshes
    Mesh* mesh1 = createMesh(sources1, loads1);
    Mesh* mesh2 = createMesh(sources2, loads2);

    // Create a circuit with the meshes
    std::vector<Mesh*> meshes = {mesh1, mesh2};
    Circuit* circuit = createCircuit(meshes);

    // Simulate the circuit
    Simulator simulator(circuit);
    simulator.runSimulation();

    // Print electric properties
    std::cout << "Mesh 1 Current: " << std::abs(circuit->getMeshCurrents()[0])
              << "/_" << (180.0 / PI) * std::arg(circuit->getMeshCurrents()[0]) << " A" << std::endl;
    std::cout << "Mesh 2 Current: " << std::abs(circuit->getMeshCurrents()[1])
              << "/_" << (180.0 / PI) * std::arg(circuit->getMeshCurrents()[1]) << " A" << std::endl;

    // Print matrices and vectors
    std::cout << "Impedance Matrix:" << std::endl;
    printMatrix(circuit->getImpedanceMatrix());

    std::cout << "Current Vector:" << std::endl;
    printVector(circuit->getCurrentVector());

    std::cout << "Voltage Vector:" << std::endl;
    printVector(circuit->getVoltageVector());

    // Clean up allocated memory
    delete voltageSource1;
    delete voltageSource2;
    delete load1;
    delete load2;
    delete load3;
    delete mesh1;
    delete mesh2;
    delete circuit;

    return 0;
}
