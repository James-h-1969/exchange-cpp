#include "orderbook/orderbook.h"

OrderBook::OrderBook(OrderBookMeta order_book_meta) {
    _order_book_meta = order_book_meta;
}

OrderBookInsertResponse OrderBook::insert_order(const OrderBookInsertRequest& request) {
    // MATCH AGAINST OPPOSITE SIDE
    uint64_t remaining_volume = request.volume;
    while (remaining_volume > 0) {
        int64_t price = 0;
    }

    // DEAL WITH REMAINING VOLUME
    if (remaining_volume > 0) {

    }

    OrderBookInsertResponse response = {
        .status=1,
        .out_trades=nullptr,
        .out_trade_count=0,
    };

    return response;
}

OrderBookDeleteResponse OrderBook::delete_order(const OrderBookDeleteRequest& request) {

}