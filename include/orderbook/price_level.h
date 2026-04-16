#pragma once 

#include <algorithm>
#include <unordered_map>

#include "shared_types.h"

struct PriceLevelNode 
{
    u64 resting_order_id;

    PriceLevelNode* next = nullptr; 
    PriceLevelNode* prev = nullptr;

    void remove_from_list();
};

class PriceLevel {  
public:
    PriceLevel(): price_(0) {}; // why?
    PriceLevel(i64 price): price_(price), length_(0) {};

    void insert(PriceLevelNode* node);

    void match(
        u64 order_id,
        u64* remaining_volume, 
        u16* trade_count, 
        std::unordered_map<u64, RestingOrder> order_id_to_resting_order,
        Trades& trades
    ); 

    u16 get_length() {
        return length_;
    }

private:
    PriceLevelNode* head_ = nullptr;
    PriceLevelNode* tail_ = nullptr;
    i64 price_;
    u16 length_;
};