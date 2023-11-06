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
#include <memory>

// Function prototypes for creating components
std::unique_ptr<ACVoltageSource> createACVoltageSource(double magnitude, double phase, double frequency);
std::unique_ptr<Load> createLoad(double magnitude, double phase);
std::unique_ptr<Mesh> createMesh(const std::vector<Source*>& sources, const std::vector<Load*>& loads);
std::unique_ptr<Circuit> createCircuit(const std::vector<Mesh*>& meshes);
void printMatrix(const Eigen::MatrixXcd& matrix);
void printVector(const Eigen::VectorXcd& vector);

// Function definitions for creating components
std::unique_ptr<ACVoltageSource> createACVoltageSource(double magnitude, double phase, double frequency) {
    return std::make_unique<ACVoltageSource>(magnitude, phase, frequency);
}

std::unique_ptr<Load> createLoad(double magnitude, double phase) {
    return std::make_unique<Load>(magnitude, phase);
}

std::unique_ptr<Mesh> createMesh(const std::vector<Source*>& sources, const std::vector<Load*>& loads) {
    return std::make_unique<Mesh>(sources, loads);
}

std::unique_ptr<Circuit> createCircuit(const std::vector<Mesh*>& meshes) {
    return std::make_unique<Circuit>(meshes);
}

void printMatrix(const Eigen::MatrixXcd& matrix) {
    for (int i = 0; i < matrix.rows(); ++i) {
        for (int j = 0; j < matrix.cols(); ++j) {
            std::complex<double> val = matrix(i, j);
            std::cout << "(" << val.real();
            if (val.imag() >= 0) std::cout << "+";
            std::cout << val.imag() << "i) ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printVector(const Eigen::VectorXcd& vector) {
    for (int i = 0; i < vector.size(); ++i) {
        std::complex<double> val = vector(i);
        std::cout << "(" << val.real();
        if (val.imag() >= 0) std::cout << "+";
        std::cout << val.imag() << "i) ";
    }
    std::cout << std::endl;
}

int main() {
    // Creating voltage sources
    auto voltageSource1 = createACVoltageSource(60.0, 20.0, 60.0); // 60V, 20°, 60Hz
    auto voltageSource2 = createACVoltageSource(-10.0, 70.0, 60.0); // -10V, 70°, 60Hz

    // Creating loads
    auto load1 = createLoad(30.0, 30.0); // 30/_30° ohms
    auto load2 = createLoad(40.0, 60.0); // 40/_60° ohms
    auto load3 = createLoad(15.0, 20.0); // 15/_20° ohms

    // Creating the first mesh with the loads
    std::vector<Source*> sources1 = {voltageSource1.get()};
    std::vector<Load*> loads1 = {load1.get(), load3.get()};

    std::vector<Source*> sources2 = {voltageSource2.get()};
    std::vector<Load*> loads2 = {load3.get(), load2.get()};

    auto mesh1 = createMesh(sources1, loads1);
    auto mesh2 = createMesh(sources2, loads2);

    // Creating a circuit with the meshes
    std::vector<Mesh*> meshes = {mesh1.get(), mesh2.get()};
    auto circuit = createCircuit(meshes);

    // Simulating the circuit
    Simulator simulator(circuit.get());
    simulator.runSimulation();

    // Printing electric properties
    std::cout << "Mesh 1 Current: " << std::abs(circuit->getMeshCurrents()[0]) << "/_" << (180.0 / PI) * std::arg(circuit->getMeshCurrents()[0]) << " A" << std::endl;
    std::cout << "Mesh 2 Current: " << std::abs(circuit->getMeshCurrents()[1]) << "/_" << (180.0 / PI) * std::arg(circuit->getMeshCurrents()[1]) << " A" << std::endl;

    // Printing matrices and vectors using Eigen's stream operators and manual loops
    std::cout << "Impedance Matrix:" << std::endl;
    printMatrix(circuit->getImpedanceMatrix());

    std::cout << "Current Vector:" << std::endl;
    printVector(circuit->getCurrentVector());

    std::cout << "Voltage Vector:" << std::endl;
    printVector(circuit->getVoltageVector());

    // Memory is automatically cleaned up by unique_ptr
    return 0;
}