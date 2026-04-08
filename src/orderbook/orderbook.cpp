#include "orderbook/orderbook.h"

OrderBook::OrderBook(OrderBookMeta order_book_meta) {
    _order_book_meta = order_book_meta;
}

OrderBookInsertResponse OrderBook::insert_order(const OrderBookInsertRequest& request) {
    // MATCH AGAINST OPPOSITE SIDE
    uint64_t remaining_volume = request.volume;
    int16_t trade_count = 0;
    if (request.side == Side::BUY) { 
        for (uint64_t opposite_side_price: asks_) {
            if (opposite_side_price <= request.price && remaining_volume > 0) {
                price_to_price_level_[opposite_side_price].match(&remaining_volume, &trade_count);
            } else {
                break;
            }
        }
    } else {
        for (uint64_t opposite_side_price: bids_) {
            if (opposite_side_price >= request.price && remaining_volume > 0) {
                price_to_price_level_[opposite_side_price].match(&remaining_volume, &trade_count);
            } else {
                break;
            }
        }
    }

    // DEAL WITH REMAINING VOLUME
    if (remaining_volume > 0) {
        if (contains_key(price_to_price_level_, request.price)) {
            PriceLevelNode* price_level_node = new PriceLevelNode{remaining_volume, 0};
            price_to_price_level_[request.price].insert(price_level_node);
        } else {
            PriceLevel price_level = PriceLevel();
            PriceLevelNode* price_level_node = new PriceLevelNode{remaining_volume, 0};
            price_level.insert(price_level_node);
            price_to_price_level_[request.price] = price_level;
            if (request.side == Side::BUY) {
                bids_.insert(request.price);
            } else {
                asks_.insert(request.price);
            }
        }
    }

    OrderBookInsertResponse response = {
        .status=1,
        .out_trades=nullptr,
        .out_trade_count=trade_count,
    };

    return response;
}

OrderBookDeleteResponse OrderBook::delete_order(const OrderBookDeleteRequest& request) {

}