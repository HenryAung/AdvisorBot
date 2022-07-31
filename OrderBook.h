#pragma once
#include"OrderBookEntry.h"
#include"CSVReader.h"
#include<string>
#include<vector>

using namespace std; 


class OrderBook { 
    public: 
    /** construct, reading a csv data file */ 
        OrderBook(string filename);

    /** return vector of all know products in the data set*/ 
        vector<string> getKnownProducts(); 

    /** return vector of all time steps in the data set*/ 
        vector<string> getAllTimeStep(); 

    /** return vector of filtered obe according to the sent filters command*/ 
        vector<OrderBookEntry> getFilteredOBE(string product, OrderType orderType, string & timestamp); 
        
    /** returns the earliest time in the order book */ 
        string getEarliestTime(); 

    /** returns the next time after the sent time is the orderbook. If there is no next_time stamp, wraps around to the start. */ 
        string getNextTime(string timestamp); 

    /** returns the previous time */ 
        string getPreviousTime(string timestamp); 

    
        static double getHighPrice(vector<OrderBookEntry> & orders);  // return the highest price of the product
        static double getlowPrice(vector<OrderBookEntry> & orders);  // return the lowest price of the product
        static double meanPrice(vector<OrderBookEntry> & orders); /** retrun vector of average values of all product */ 
    private :
        vector<OrderBookEntry> orders; 
}; 