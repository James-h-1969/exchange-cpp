#pragma once 

#include <cstdint>
#include <vector>
#include "shared_types.h"

struct OrderBookInsertResponse {
    uint8_t status;
    std::vector<Trade> out_trades;
    uint16_t out_trade_count;
};

struct OrderBookDeleteResponse {
    uint8_t status;
};

