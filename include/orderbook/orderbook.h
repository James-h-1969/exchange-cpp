#pragma once 

#include <shared_types.h>
#include "request.h"
#include "response.h"
#include <cstdint>

constexpr uint8_t instrument_name_len = 4;

struct OrderBookMeta {
    char instrument[instrument_name_len];
};

class OrderBook {
public:
    OrderBook(OrderBookMeta order_book_meta);

    [[nodiscard]] OrderBookInsertResponse insert_order(const OrderBookInsertRequest& request);
    [[nodiscard]] OrderBookDeleteResponse delete_order(const OrderBookDeleteRequest& request);
private:
    OrderBookMeta _order_book_meta;
};