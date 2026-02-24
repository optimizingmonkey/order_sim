#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

class OrderBook {
public:
    // Pre-allocate arrays to handle prices up to $2,000.00 (200,000 cents)
    OrderBook() : bids(200005, 0), asks(200005, 0), max_bid(0), min_ask(200000) {}

    void limit_order(double price, int quantity, bool is_buy) {
        // Convert floating point price to an exact integer index (1 tick = $0.01)
        int price_idx = std::round(price * 100.0);

        if (is_buy) {
            // MATCHING: Instantly jump to the lowest available ask
            for (int ask_idx = min_ask; ask_idx <= price_idx && quantity > 0; ++ask_idx) {
                if (asks[ask_idx] > 0) {
                    int trade_qty = std::min(quantity, asks[ask_idx]);
                    quantity -= trade_qty;
                    asks[ask_idx] -= trade_qty;
                }
            }

            // ADDING: Place remaining volume directly into the array
            if (quantity > 0) {
                bids[price_idx] += quantity;
                if (price_idx > max_bid) {
                    max_bid = price_idx; // Update the highest bid tracker
                }
            }
            
            // CLEANUP: Fast-forward min_ask if we bought out the lowest levels
            while (min_ask < 200000 && asks[min_ask] == 0) {
                min_ask++;
            }

        } else {
            // MATCHING: Instantly jump to the highest available bid
            for (int bid_idx = max_bid; bid_idx >= price_idx && quantity > 0; --bid_idx) {
                if (bids[bid_idx] > 0) {
                    int trade_qty = std::min(quantity, bids[bid_idx]);
                    quantity -= trade_qty;
                    bids[bid_idx] -= trade_qty;
                }
            }

            // ADDING: Place remaining volume directly into the array
            if (quantity > 0) {
                asks[price_idx] += quantity;
                if (price_idx < min_ask) {
                    min_ask = price_idx; // Update the lowest ask tracker
                }
            }

            // CLEANUP: Fast-forward max_bid if we sold out the highest levels
            while (max_bid > 0 && bids[max_bid] == 0) {
                max_bid--;
            }
        }
    }

    void print() const {
        std::cout << "\n--- Order Book Status (O(1) Engine) ---" << std::endl;
        // Disabled for the 1M stress test, but logic remains for smaller tests
        std::cout << "Top Bid Index: " << max_bid << " | Lowest Ask Index: " << min_ask << std::endl;
        std::cout << "---------------------------------------\n" << std::endl;
    }

private:
    std::vector<int> bids; 
    std::vector<int> asks; 
    int max_bid;
    int min_ask;
};