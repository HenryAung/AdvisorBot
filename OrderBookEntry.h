#pragma once

#include<iostream>
#include <string> 
using namespace std; 

enum class OrderType { bid, ask, unknown, askSale, bidSale };

class OrderBookEntry {

        public:
            OrderBookEntry( double _price, 
                            double _amount, 
                            string _timestamp, 
                            string _product, 
                            OrderType _orderType, 
                            string username = "dataset" ); 
            
            static OrderType stringToOrderType(string s); 
            
            static bool compareByTimestampAsc(OrderBookEntry& e1, OrderBookEntry& e2) {
                return e1.timestamp < e2.timestamp; 
            }

            static bool compareByTimestampDesc(OrderBookEntry& e1, OrderBookEntry& e2) {
                return e1.timestamp > e2.timestamp; 
            }

            static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2) {
                return e1.price < e2.price; 
            }

            static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2) {
                return e1.price > e2.price; 
            }
            
            double price;
            double amount;
            string timestamp;
            string product;
            OrderType orderType;
            string username; 
};
