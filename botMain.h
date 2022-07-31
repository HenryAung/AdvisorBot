#include<iostream> 
#include<string>
#include"OrderBook.h"
#include"CSVReader.h"
#include"OrderBookEntry.h"

using namespace std; 

class botMain { 
    public:  
        botMain();
        void init(); 


    private: 
        
        void printMenu(); 
        void help(); 
        void prodPurpose();
        void maxPropuse();
        void minPurpose();
        void avgPurpose();
        void predictPurpose();
        void timePurpose();
        void stepPrupose();
        void prevPurpose(); 
        void marketStatsPurpose(); 
        void marketGainersPurpose(); 
        void marketLosersPurpose(); 

        void listProduct();
        void min(vector<string> tokens); 
        void max(vector<string> tokens); 

        double calculateAvg(vector<string> tokens); 
        void avg(vector<string>input); 

        double calculateUBPrediction(vector<string>tokens); 
        double calculateLBPrediction(vector<string>tokens); 
        void predict(vector<string>input); 

        void time(); 
        void step(); 
        void prev(); 

        void printMarketStats(); 
        void marketGainers(); 
        void marketLosers();
        
        vector<string> getUserInput();  
        void processUserInput(vector<string> input); 

        string currentTime; 

        OrderBook OrderBook{"20200317.csv"}; 
}; 