#include "OrderBook.h"

void OrderBook::add_order(int id, bool side, double price, int size) {

}

void OrderBook::order_matcher(int id, bool side, double price, int size) {
    if(!side) {
    //if side is buy
    if(!askBookHead) {
        //no seller in the market
        //insert first order to bid book
    }
    //if askbook is not empty
    //Iterate over the ask_book and see first if price matches. 
    //if leftover quantity - add to bid_book
    } else {
    if(!bidBookHead) {
        //no buyer in the market
        //insert first sell order to ask book as resting order
    }
    //match against ask_book - recursively
    //update both  bid and ask book accordingly.
    //if leftover quantity - add the order to bid_book
    }
}

void OrderBook::cancel_order(int orderId) {

}

