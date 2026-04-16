#pragma once 

#include <set>

#include "request.h"
#include "response.h"
#include "price_level.h"
#include "helpers.h"
#include "shared_types.h"

constexpr u8 instrument_name_len = 4;

struct OrderBookMeta
{
    char instrument[instrument_name_len];
};

class OrderBook
{
public:
    OrderBook(OrderBookMeta order_book_meta);

    [[nodiscard]] OrderBookInsertResponse insert_order(const OrderBookInsertRequest& request);
    [[nodiscard]] OrderBookDeleteResponse delete_order(const OrderBookDeleteRequest& request);
private:
    OrderBookMeta _order_book_meta;

    std::set<i64> bids_;
    std::set<i64> asks_;
    std::unordered_map<i64, PriceLevel> price_to_price_level_;
    std::unordered_map<u64, RestingOrder> order_id_to_resting_order;
    std::unordered_map<u64, PriceLevelNode*> order_id_to_price_level_node;
};