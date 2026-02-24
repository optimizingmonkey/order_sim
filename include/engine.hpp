#pragma once
#include <queue>
#include <vector>
#include <functional>
#include <iostream>

struct Event {
    double timestamp;
    // Using a std::function allows us to pass any logic (lambda) into the event
    std::function<void()> callback;

    // Min-heap logic: the priority_queue puts the "largest" at the top,
    // so we invert the comparison to get the smallest timestamp first.
    bool operator>(const Event& other) const {
        return timestamp > other.timestamp;
    }
};

class Engine {
public:
    void add_event(double ts, std::function<void()> cb) {
        pq.push({ts, std::move(cb)});
    }

    void run();

private:
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> pq;
    double current_time = 0.0;
};
