#include "orderbook/orderbook.h"

OrderBook::OrderBook(OrderBookMeta order_book_meta) {
    _order_book_meta = order_book_meta;
}

OrderBookInsertResponse OrderBook::insert_order(const OrderBookInsertRequest& request) {
    uint64_t remaining_volume = request.volume;
    uint16_t trade_count = 0;
    if (request.side == Side::BUY) { 
        for (int64_t opposite_side_price: asks_) {
            if (opposite_side_price <= request.price && remaining_volume > 0) {
                price_to_price_level_[opposite_side_price].match(&remaining_volume, &trade_count, order_id_to_resting_order);
            } else {
                break;
            }
        }
    } else {
        for (int64_t opposite_side_price: bids_) {
            if (opposite_side_price >= request.price && remaining_volume > 0) {
                price_to_price_level_[opposite_side_price].match(&remaining_volume, &trade_count, order_id_to_resting_order);
            } else {
                break;
            }
        }
    }

    /*
    Matching against the other side is complete. If any remaining volume, let it rest in the book.
    */
    if (remaining_volume > 0) {
        PriceLevelNode* price_level_node = new PriceLevelNode{request.order_id};
        RestingOrder resting_order = {
            .order_id=request.order_id,
            .price=request.price,
            .volume=request.volume,
        };
        order_id_to_price_level_node[request.order_id] = price_level_node;
        order_id_to_resting_order[request.order_id] = resting_order;
        
        if (contains_key(price_to_price_level_, request.price)) {
            price_to_price_level_[request.price].insert(price_level_node);
        } else {
            PriceLevel price_level = PriceLevel();
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
    if (!contains_key(order_id_to_price_level_node, request.order_id)) {
        OrderBookDeleteResponse response = {
            .status=0,
        };
        return response;
    };

    RestingOrder resting_order = order_id_to_resting_order[request.order_id];
    PriceLevelNode* price_level = order_id_to_price_level_node[request.order_id];

    price_level->remove_from_list();

    if (price_to_price_level_[resting_order.price].length == 0) {
        price_to_price_level_.erase(resting_order.price);
    }

    order_id_to_price_level_node.erase(request.order_id);
    order_id_to_resting_order.erase(request.order_id);

    OrderBookDeleteResponse response = {
        .status=1
    };

    return response;
}