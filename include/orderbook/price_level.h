#pragma once 

#include <cstdint>
#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "shared_types.h"

struct PriceLevelNode {
    uint64_t order_id;

    PriceLevelNode* next = nullptr; 
    PriceLevelNode* prev = nullptr;

    void remove_from_list();
};

class PriceLevel {  
public:
    PriceLevel(): price_(0) {};
    PriceLevel(int64_t price): price_(price) {};
    void insert(PriceLevelNode* node);
    void match(
        uint64_t order_id,
        uint64_t* remaining_volume, 
        uint16_t* trade_count, 
        std::unordered_map<uint64_t,
        RestingOrder> order_id_to_resting_order,
        std::vector<Trade>& trades
    ); 

    int16_t length = 0;
private:
    PriceLevelNode* head_ = nullptr;
    PriceLevelNode* tail_ = nullptr;
    int64_t price_;
};