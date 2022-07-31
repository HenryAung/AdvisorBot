#include<iostream>
#include"botMain.h"
#include"OrderBook.h"
#include"OrderBookEntry.h"
#include"CSVReader.h"

using namespace std; 



int main () { 
    botMain bot{}; 
    bot.init(); 
    
    return 0; 
};