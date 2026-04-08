#pragma once 

#include <cstdint>
#include <algorithm>
#include <iostream>

struct PriceLevelNode {
    uint64_t volume;
    uint64_t trade_id;

    PriceLevelNode* next = nullptr; 
    PriceLevelNode* prev = nullptr;
};

class PriceLevel {  
public:
    void insert(PriceLevelNode* node);
    void match(uint64_t* remaining_volume, int16_t* trade_count); 
private:
    PriceLevelNode* head_ = nullptr;
    PriceLevelNode* tail_ = nullptr;
};