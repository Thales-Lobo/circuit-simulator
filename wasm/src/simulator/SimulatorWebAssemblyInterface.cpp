#include "simulator/Simulator.hpp"
#include <emscripten/bind.h>

// Interface functions for creating and destroying Simulator objects
extern "C" {
    Simulator* CreateSimulator(Circuit* circuit) {
        return new Simulator(std::shared_ptr<Circuit>(circuit));
    }

    void DestroySimulator(Simulator* simulator) {
        delete simulator;
    }
}

// Emscripten binding
EMSCRIPTEN_BINDINGS(simulator_module) {
    emscripten::class_<Simulator>("Simulator")
        .smart_ptr<std::shared_ptr<Simulator>>("shared_ptr<Simulator>")
        .class_function("create", &CreateSimulator, emscripten::allow_raw_pointers())
        .function("runSimulation", &Simulator::runSimulation)
        .function("assignCurrentToLoads", &Simulator::assignCurrentToLoads)
        .function("determineLoadCurrent", &Simulator::determineLoadCurrent)
        .function("assignCurrentToVoltageSources", &Simulator::assignCurrentToVoltageSources);
}
