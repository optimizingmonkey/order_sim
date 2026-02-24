#pragma once
#include <map>
#include <iostream>

class OrderBook {
public:
    // Side: true for Buy (Bid), false for Sell (Ask)
    void limit_order(double price, int quantity, bool is_buy) {
        if (is_buy) {
            bids[price] += quantity;
        } else {
            asks[price] += quantity;
        }
    }

    void print() const {
        std::cout << "\n--- Order Book Status ---" << std::endl;
        std::cout << "Asks (Sells):" << std::endl;
        for (auto it = asks.rbegin(); it != asks.rend(); ++it) {
            std::cout << "  " << it->first << " : " << it->second << std::endl;
        }
        std::cout << "Bids (Buys):" << std::endl;
        for (auto it = bids.rbegin(); it != bids.rend(); ++it) {
            std::cout << "  " << it->first << " : " << it->second << std::endl;
        }
    }

private:
    std::map<double, int> bids; // High price first
    std::map<double, int> asks; // Low price first
};
