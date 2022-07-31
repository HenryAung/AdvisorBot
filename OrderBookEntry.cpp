#include<iostream>
#include<string>
#include "OrderBookEntry.h"

using namespace std; 

OrderBookEntry::OrderBookEntry( double _price, 
                                double _amount, 
                                string _timestamp, 
                                string _product, 
                                OrderType _orderType, 
                                string _username)
              : price(_price), 
                amount(_amount), 
                timestamp(_timestamp), 
                product(_product), 
                orderType(_orderType), 
                username(_username)
{

}; 

OrderType OrderBookEntry::stringToOrderType(string s) { 
    if (s == "ask") { 
      return OrderType::ask; 
    }

    if (s == "bid") { 
      return OrderType::bid; 
    }
    
    return OrderType::unknown; 
}; 

