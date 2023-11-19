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
std::shared_ptr<ACVoltageSource> createACVoltageSource(double magnitude, double phase, double frequency);
std::shared_ptr<Load> createLoad(double magnitude, double phase);
std::shared_ptr<Mesh> createMesh(std::vector<std::shared_ptr<Source>>& sources, std::vector<std::shared_ptr<Load>>& loads);
std::shared_ptr<Circuit> createCircuit(std::vector<std::shared_ptr<Mesh>>& meshes);
void printMatrix(const Eigen::MatrixXcd& matrix);
void printVector(const Eigen::VectorXcd& vector);

// Function definitions for creating components
// Creates an AC voltage source
std::shared_ptr<ACVoltageSource> createACVoltageSource(double magnitude, double phase, double frequency) {
    return std::make_shared<ACVoltageSource>(magnitude, phase, frequency);
}

// Creates a load with specified magnitude and phase
std::shared_ptr<Load> createLoad(double magnitude, double phase) {
    return std::make_shared<Load>(magnitude, phase);
}

// Creates a mesh from given sources and loads
std::shared_ptr<Mesh> createMesh(std::vector<std::shared_ptr<Source>>& sources, std::vector<std::shared_ptr<Load>>& loads) {
    return std::make_shared<Mesh>(sources, loads);
}

// Creates a circuit from a collection of meshes
std::shared_ptr<Circuit> createCircuit(std::vector<std::shared_ptr<Mesh>>& meshes) {
    return std::make_shared<Circuit>(meshes);
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
    // Create voltage sources using shared pointers
    auto voltageSource1 = createACVoltageSource(60.0, 20.0, 60.0); // 60V, 20°, 60Hz
    auto voltageSource2 = createACVoltageSource(10.0, 70.0, 60.0); // -10V, 70°, 60Hz

    // Create loads using shared pointers
    auto load1 = createLoad(30.0, 0.0); // 30 ohms at 30°
    auto load2 = createLoad(40.0, 0.0); // 40 ohms at 60°
    auto load3 = createLoad(15.0, 0.0); // 15 ohms at 20°

    // Create the first mesh with the loads
    std::vector<std::shared_ptr<Source>> sources1   = {voltageSource1};
    std::vector<std::shared_ptr<Load>> loads1       = {load1, load3};
    auto mesh1 = std::make_shared<Mesh>(sources1, loads1);

    // Create the second mesh with the loads
    std::vector<std::shared_ptr<Source>> sources2   = {voltageSource2};
    std::vector<std::shared_ptr<Load>> loads2       = {load3, load2};
    auto mesh2 = std::make_shared<Mesh>(sources2, loads2);

    // Create a circuit with the meshes
    std::vector<std::shared_ptr<Mesh>> meshes = {mesh1, mesh2};
    auto circuit = createCircuit(meshes);

    // Simulate the circuit
    Simulator simulator(circuit);
    simulator.runSimulation();
    
    // Output the results
    std::cout << "--Results--" << std::endl << std::endl;

    // Print matrices and vectors
    std::cout << "Impedance Matrix:" << std::endl;
    printMatrix(circuit->getImpedanceMatrix());

    std::cout << "Voltage Vector:" << std::endl;
    printVector(circuit->getVoltageVector());

    std::cout << "Current Vector:" << std::endl;
    printVector(circuit->getCurrentVector());

    return 0;
}
