#pragma once 

#include <shared_types.h>
#include <cstdint>
#include <set>

#include "request.h"
#include "response.h"
#include "price_level.h"
#include "helpers.h"

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

    std::set<int64_t> bids_;
    std::set<int64_t> asks_;

    std::unordered_map<int64_t, PriceLevel> price_to_price_level_;

    std::unordered_map<uint64_t, RestingOrder> order_id_to_resting_order;
    std::unordered_map<uint64_t, PriceLevelNode*> order_id_to_price_level_node;
};