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
    /*
    TestSimpleBuy: insert a single buy into the orderbook and make sure no trades happened
    */
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
    /*
    TestSimpleMatch: insert a buy and sell at the same price and make sure they trade
    */
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

TEST_F(OrderBookTest, TestSimpleMultiMatchSamePriceLevel) {
    /*
    TestSimpleMatch: insert a buy and 2 sells at the same price and make sure they trade
    */
    OrderBookInsertRequest request = {
        .order_id=1,
        .price=10,
        .volume=10,
        .side=Side::BUY,
    };
    OrderBookInsertRequest request_match = {
        .order_id=2,
        .price=10,
        .volume=5,
        .side=Side::SELL,
    };
    OrderBookInsertRequest request_match_2 = {
        .order_id=3,
        .price=10,
        .volume=5,
        .side=Side::SELL,
    };
    OrderBookInsertResponse response1 = orderbook_->insert_order(request_match);
    OrderBookInsertResponse response2 = orderbook_->insert_order(request_match_2);
    OrderBookInsertResponse response3 = orderbook_->insert_order(request);

    ASSERT_EQ(response1.out_trade_count, 0);
    ASSERT_EQ(response2.out_trade_count, 0);
    ASSERT_EQ(response3.out_trade_count, 2);
}

TEST_F(OrderBookTest, TestSimpleMultiMatchDiffPriceLevel) {
    /*
    TestSimpleMatch: insert a buy and 2 sells at the different prices and make sure they trade
    */
    OrderBookInsertRequest request = {
        .order_id=1,
        .price=10,
        .volume=10,
        .side=Side::BUY,
    };
    OrderBookInsertRequest request_match = {
        .order_id=1,
        .price=10,
        .volume=5,
        .side=Side::SELL,
    };
    OrderBookInsertRequest request_match_2 = {
        .order_id=1,
        .price=8,
        .volume=5,
        .side=Side::SELL,
    };
    OrderBookInsertResponse response1 = orderbook_->insert_order(request_match);
    OrderBookInsertResponse response2 = orderbook_->insert_order(request_match_2);
    OrderBookInsertResponse response3 = orderbook_->insert_order(request);

    ASSERT_EQ(response1.out_trade_count, 0);
    ASSERT_EQ(response2.out_trade_count, 0);
    ASSERT_EQ(response3.out_trade_count, 2);
};

TEST_F(OrderBookTest, TestSimpleDelete) {
    /*
    Simple insert and delete to make sure no errors in the program
    */

    OrderBookInsertRequest request = {
        .order_id=1,
        .price=10,
        .volume=10,
        .side=Side::BUY,
    };
    OrderBookInsertResponse insert_response = orderbook_->insert_order(request);

    OrderBookDeleteRequest delete_request = {
        .order_id=1,
    };
    OrderBookDeleteResponse delete_response = orderbook_->delete_order(delete_request);

    ASSERT_EQ(delete_response.status, 1);
}

TEST_F(OrderBookTest, TestDeleteWrongId) {
    /*
    Simple insert and then delete with an invalid id
    */

    OrderBookInsertRequest request = {
        .order_id=1,
        .price=10,
        .volume=10,
        .side=Side::BUY,
    };
    OrderBookInsertResponse insert_response = orderbook_->insert_order(request);

    OrderBookDeleteRequest delete_request = {
        .order_id=2,
    };
    OrderBookDeleteResponse delete_response = orderbook_->delete_order(delete_request);

    ASSERT_EQ(delete_response.status, 0);
}

TEST_F(OrderBookTest, TestDeleteNoVolumeLeft) {
    /*
    Test if an insert, then delete, and then new insert comes in that would of matched 
    with the initial volume, make sure that it has no volume
    */

    OrderBookInsertRequest request = {
        .order_id=1,
        .price=10,
        .volume=10,
        .side=Side::BUY,
    };
    OrderBookInsertResponse insert_response = orderbook_->insert_order(request);

    OrderBookDeleteRequest delete_request = {
        .order_id=1,
    };
    OrderBookDeleteResponse delete_response = orderbook_->delete_order(delete_request);

    OrderBookInsertRequest request2 = {
        .order_id=1,
        .price=10,
        .volume=10,
        .side=Side::SELL,
    };
    OrderBookInsertResponse insert_response_2 = orderbook_->insert_order(request2);

    ASSERT_EQ(insert_response_2.out_trade_count, 0);
}
