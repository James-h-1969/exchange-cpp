#include "orderbook/orderbook.h"
#include <gtest/gtest.h>

class OrderBookTest: public testing::Test {
    protected:
        OrderBookTest() {
            OrderBookMeta orderbook_meta = {
                .instrument="XAU",
            };

            orderbook_ = new OrderBook(orderbook_meta);
        }

        OrderBook* orderbook_;
};

TEST_F(OrderBookTest, TestSimpleBuy) {
    OrderBookInsertRequest request = {
        .order_id=1,
        .price=10,
        .volume=10,
        .side=Side::BUY,
    };
    OrderBookInsertResponse response = orderbook_->insert_order(request);
    ASSERT_EQ(response.out_trade_count, 0);
}

TEST_F(OrderBookTest, TestSimpleMatch) {
    OrderBookInsertRequest request = {
        .order_id=1,
        .price=10,
        .volume=10,
        .side=Side::BUY,
    };
    OrderBookInsertRequest request_match = {
        .order_id=1,
        .price=10,
        .volume=10,
        .side=Side::SELL,
    };
    OrderBookInsertResponse response = orderbook_->insert_order(request);
    ASSERT_EQ(response.out_trade_count, 0);
    OrderBookInsertResponse response_match = orderbook_->insert_order(request_match);
    ASSERT_EQ(response_match.out_trade_count, 1);
}