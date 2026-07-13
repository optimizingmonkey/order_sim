# QuantSim — Event-Driven Limit Order Book Simulator

I built a high-performance, event-driven market simulator built in C++20. It replays timestamped order flow through a custom O(1) direct-mapped limit order book and executes trading strategy logic against it, benchmarked at processing **1,000,000 simulated limit orders in ~118ms** (Release build, Apple Silicon).

## Overview

QuantSim models the core mechanics of an exchange matching engine:

- A **priority-queue-driven simulation clock** (`Engine`) that processes market events strictly in timestamp order, enforcing causality (no event can be processed out of chronological sequence).
- An **O(1) array-indexed order book** (`OrderBook`) that maps prices directly to array indices (1 tick = $0.01), eliminating the need for tree/map lookups (`O(log n)`) or sorted-vector shifting during matching.
- A **strategy layer** that consumes book state and market events to generate trades against the simulated tape.

The project's primary engineering goal was to explore how far a matching engine's raw throughput could be pushed by trading generality (arbitrary price precision, sparse books) for speed (fixed price grid, direct indexing) — a real tradeoff made by low-latency trading infrastructure.

## Architecture

```
main.cpp
  ├── load_market_data()   → parses CSV, schedules events on the Engine
  ├── Engine::run()        → min-heap event loop, advances simulation clock
  └── OrderBook            → O(1) matching engine
        ├── bids[] / asks[]   → direct-mapped arrays (price → quantity)
        ├── max_bid / min_ask → best price pointers, incrementally maintained
        └── limit_order()     → match-then-post logic per incoming order
```

**Key design choice:** instead of a `std::map<price, level>` (log-time lookups) or a sorted `std::vector` (linear shifts on insert), the book pre-allocates a flat array sized to the maximum expected price range and indexes directly via `round(price * 100)`. This trades memory footprint (fixed array size regardless of how sparse the book is) for guaranteed constant-time access.

## Performance

| Version / Architecture | Build Type | Average (1M events) |
| :--- | :--- | :--- |
| `std::map` OrderBook | Debug | ~857,000 µs |
| `std::map` OrderBook | Release (-O3) | ~126,000 µs |
| `std::vector` (Sorted) | Release (-O3) | ~146,000 µs |
| **O(1) Direct-Mapped Array** | **Release (-O3)** | **~118,600 µs** |

See `BENCHMARKS.md` for full run-by-run data.

## Build & Run

```bash
mkdir build && cd build
cmake ..
make

# Generate synthetic stress-test data (1M orders)
./generate_data

# Run the simulation
./sim_engine
```

Requires CMake ≥ 3.10 and a C++20 compiler. The Release build flags (`-O3 -march=native`) are tuned for Apple Silicon; adjust `-march` for other targets.

## Project Structure

```
include/
  engine.hpp       — event queue + simulation clock
  order_book.hpp    — O(1) matching engine
src/
  engine.cpp
  order_book.cpp
  main.cpp          — data loading + simulation entrypoint
  generate_data.cpp — synthetic order flow generator (seeded, deterministic)
data/
  market_data.csv    — small hand-crafted example book
  stress_test.csv    — 1M-row generated stress test (via generate_data)
BENCHMARKS.md
```
