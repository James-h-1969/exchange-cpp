#include "orderbook/price_level.h"

/*
Removes a resting order from the price level
*/
void PriceLevelNode::remove_from_list() 
{
    if (prev != nullptr) { // Not the first node
        prev->next = next;
    }

    if (next != nullptr) { // Not the last node
        next->prev = prev;
    }
}

/*
Inserts a resting order into the price level
*/
void PriceLevel::insert(PriceLevelNode* node) 
{
    if (head_ == nullptr) // List is empty
    { 
        head_ = node;
        tail_ = node;
    } else // Add to the end of the list
    { 
        tail_->next = node;
        node->prev = tail_;
        tail_ = node;
    }

    length++;
};

void PriceLevel::match(
    uint64_t order_id,
    uint64_t* volume, 
    uint16_t* trade_count,
    std::unordered_map<uint64_t,
    RestingOrder> order_id_to_resting_order,
    std::vector<Trade>& trades
) 
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
            Trade t = {
                .aggressor_order_id=order_id,
                .passive_order_id=head->order_id,
                .price=price_,
                .volume=matched_volume
            };
            trades.push_back(t);
            std::cout << trades.size() << std::endl;
        }

        // Pop from front of list 
        if (order_id_to_resting_order[head->order_id].volume == 0) {
            PriceLevelNode* to_delete = head_;
            head_ = head_->next;
            delete to_delete;
        }
    }
};