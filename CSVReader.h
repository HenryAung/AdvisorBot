#pragma once 
#include<vector>
#include"OrderBookEntry.h"
#include<string> 

using namespace std; 

class CSVReader { 
    public : 
        CSVReader();
        static vector<OrderBookEntry> readCSV(string csvFile);  
        static vector<string> tokenise(string csvLine, char seperator); 
        static OrderBookEntry stringsToOBE(string price, string amount, string timestamp, string product, OrderType OrderType); 

    private :
        
        static OrderBookEntry stringsToOBE(vector<string> strings); 
}; 