#include<iostream>

#include "engine.hpp"

void Engine::run() {
    std::cout << "--- Simulation Started ---" << std::endl;

    while (!pq.empty()) {
        // 1. Get the earliest event
        // Use a reference to avoid copying the event data (Efficiency)
        const Event& event = pq.top();

        // 2. Safety Check: Ensure time only moves forward
        // In quant, "causality" is everything. You can't process an event 
        // that happened in the past.
        if (event.timestamp < current_time) {
            std::cerr << "Error: Event scheduled in the past at " << event.timestamp << std::endl;
            pq.pop();
            continue;
        }

        // 3. Advance the Simulation Clock
        current_time = event.timestamp;

        // 4. Execute the event logic
        // We use a local copy of the callback before popping to stay safe
        auto task = std::move(event.callback);
        
        // 5. Remove the event from the queue
        pq.pop();

        // 6. Fire the task
        if (task) {
            task();
        }
    }

    std::cout << "--- Simulation Finished at Time: " << current_time << " ---" << std::endl;
}

signed main(){
  cout<<"Hello, my first project!";
}
