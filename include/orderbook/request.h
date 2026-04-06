#pragma once 

#include <cstdint>
#include "shared_types.h"

struct OrderBookInsertRequest {
    uint64_t order_id;
    int64_t price;
    uint64_t volume;
    Side side;
    uint8_t padding[7];
};

struct OrderBookDeleteRequest {
    uint64_t order_id;
};