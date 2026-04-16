#pragma once 

#include "shared_types.h"

struct OrderBookInsertResponse
{
    u8 status;
    Trades out_trades;
    u16 out_trade_count;
};

struct OrderBookDeleteResponse
{
    u8 status;
};

