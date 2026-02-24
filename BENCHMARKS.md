# Quant Simulator Performance Benchmarks

**Hardware:** Apple Silicon (M-Series)
**Event Count:** 1,000,000 simulated limit orders

| Date | Version / Architecture | Build Type | Run 1 | Run 2 | Run 3 | Average |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Feb 24 | v1.0 - `std::map` OrderBook | Debug | 847k µs | 851k µs | 849k µs | **~857,000 µs** |
| Feb 24 | v1.0 - `std::map` OrderBook | Release (-O3) | 128k µs | 125k µs | 125k µs | **~126,000 µs** |
| Feb 24 | v1.1 - `std::vector` (Sorted) | Release (-O3) | 147k µs | 145k µs | 146k µs | **~146,000 µs** |
| Feb 25 | v2.0 - `O(1)` Direct-Mapped Array | Release (-O3) | 120k µs | 118k µs | 118k µs | **~118,600 µs** |

*Note: The O(1) architecture achieved the fastest time by eliminating all searching and shifting, relying entirely on direct memory indexing.*