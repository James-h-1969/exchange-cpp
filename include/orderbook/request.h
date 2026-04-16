#pragma once 

#include "shared_types.h"

struct OrderBookInsertRequest 
{
    u64 order_id;
    i64 price;
    u64 volume;
    Side side;
    u8 padding[7];
};

struct OrderBookDeleteRequest
{
    u64 order_id;
};