#include "orderbook/price_level.h"

void PriceLevel::insert(PriceLevelNode* node) 
{
    std::cout << "INSERTING!\n";
    if (head_ == nullptr) 
    { 
        // List is empty
        head_ = node;
        tail_ = node;
    } else {
        // Add to last element, change the tail pointer
        tail_->next = node;
        node->prev = tail_;
        tail_ = node;
    }
};

void PriceLevel::match(uint64_t* volume, int16_t* trade_count) 
{
    std::cout << "MATCHING\n";
    while (*volume > 0 && head_ != nullptr) 
    {
        PriceLevelNode* head = head_;
        uint64_t matched_volume = std::min(*volume, head->volume);

        // Trade that matched volume (create trade here)
        head->volume -= matched_volume;
        *volume -= matched_volume;

        if (matched_volume > 0) {
            *trade_count += 1;
        }

        // Pop from front of list 
        if (head->volume == 0) {
            PriceLevelNode* to_delete = head_;
            head_ = head_->next;
            delete to_delete;
        }
    }
};