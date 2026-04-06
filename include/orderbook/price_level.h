#pragma once 

#include <cstdint>

struct PriceLevelNode {
    uint64_t volume;
    uint64_t trade_id;

    PriceLevelNode* next = nullptr; 
    PriceLevelNode* prev = nullptr;
};

class PriceLevel {  
public:
    void insert(PriceLevel* node);
    uint64_t match(uint64_t volume); 
private:
    PriceLevelNode* head = nullptr;
    PriceLevelNode* tail = nullptr;
};