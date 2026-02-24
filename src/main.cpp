#include "engine.hpp"
#include <iostream>

int main() {
    Engine sim;

    // Schedule events out of order
    sim.add_event(10.5, []() { std::cout << "Processing Trade at 10.5" << std::endl; });
    sim.add_event(5.2, []() { std::cout << "Market Open at 5.2" << std::endl; });
    sim.add_event(15.0, []() { std::cout << "Market Close at 15.0" << std::endl; });

    sim.run();

    return 0;
}
