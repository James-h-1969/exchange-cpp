#pragma once 

#include <vector>
#include <cstdint>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u16 = std::uint16_t;
using u8 = std::uint8_t;

enum class Side: u8
{
    BUY = 0,
    SELL = 1
};

enum OrderType {
    LIMIT,
};

struct RestingOrder
{
    u64 order_id;
    i64 price;
    u64 volume;
};

struct Trade
{
    u64 aggressor_order_id;
    u64 passive_order_id;
    i64 price;
    u64 volume;
};

using Trades = std::vector<Trade>;