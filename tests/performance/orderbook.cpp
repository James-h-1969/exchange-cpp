#include <benchmark/benchmark.h>
#include <random>

#include "shared_types.h"
#include "orderbook/orderbook.h"
#include "orderbook/request.h"

/*
Creates a vector of orders to insert (should not be included in benchmark)
*/
std::vector<OrderBookInsertRequest> generate_mock_orders(int count) {
    std::vector<OrderBookInsertRequest> orders;
    orders.reserve(count);

    std::mt19937 rng(42);
    std::uniform_int_distribution<i64> price_dist(10000, 10500);
    std::uniform_int_distribution<u64> vol_dist(1, 100);
    std::uniform_int_distribution<int> side_dist(0, 1);

    for (int i = 0; i < count; i++) {
        OrderBookInsertRequest request;
        request.order_id = i + 1;
        request.price = price_dist(rng);
        request.side = side_dist(rng) == 0 ? Side::BUY : Side::SELL;
        request.volume = vol_dist(rng);

        orders.push_back(request);
    }
    return orders;
}

/*
Generates orders and inserts them into the orderbook
*/
static void BM_orderbook_burst_insert(benchmark::State& state) {
    int num_orders_to_insert = state.range(0);

    auto requests = generate_mock_orders(num_orders_to_insert);

    for (auto _: state) {
        // Stop the clock to not time orderbook construction
        state.PauseTiming();

        OrderBookMeta meta = {
            .instrument="XAU",
        };

        OrderBook orderbook(meta);

        state.ResumeTiming();

        for (const auto& req: requests) {
            benchmark::DoNotOptimize(orderbook.insert_order(req));
        }

        benchmark::ClobberMemory();
    }

    state.SetItemsProcessed(state.iterations() * num_orders_to_insert);
}

BENCHMARK(BM_orderbook_burst_insert)->RangeMultiplier(8)->Range(8, 32768);
BENCHMARK_MAIN();   
