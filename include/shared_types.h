#pragma once 

#include <vector>
#include <cstdint>

enum class Side: uint8_t {
    BUY = 0,
    SELL = 1
};

struct RestingOrder {
    uint64_t order_id;
    int64_t price;
    uint64_t volume;
};

struct Trade {
    uint64_t aggressor_order_id;
    uint64_t passive_order_id;
    int64_t price;
    uint64_t volume;
};