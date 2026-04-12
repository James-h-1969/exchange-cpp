#include "orderbook/price_level.h"

void PriceLevelNode::remove_from_list() {
    if (prev != nullptr) {
        // Not the first node
        prev->next = next;
    }

    if (next != nullptr) {
        // Not the last node
        next->prev = prev;
    }
}

void PriceLevel::insert(PriceLevelNode* node) 
{
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

    length++;
};

void PriceLevel::match(uint64_t* volume, int16_t* trade_count, std::unordered_map<uint64_t, RestingOrder> order_id_to_resting_order) 
{
    while (*volume > 0 && head_ != nullptr) 
    {
        PriceLevelNode* head = head_;
        uint64_t matched_volume = std::min(*volume, order_id_to_resting_order[head->order_id].volume);

        // Trade that matched volume (create trade here)
        order_id_to_resting_order[head->order_id].volume -= matched_volume;
        *volume -= matched_volume;

        if (matched_volume > 0) {
            *trade_count += 1;
        }

        // Pop from front of list 
        if (order_id_to_resting_order[head->order_id].volume == 0) {
            PriceLevelNode* to_delete = head_;
            head_ = head_->next;
            delete to_delete;
        }
    }
};