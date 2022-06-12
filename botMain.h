#include<iostream> 
#include<string>

using namespace std; 

class botMain { 
    public:  
        botMain();
        void init(); 

    private: 
        void processUserInput(string input); 
        string getUserInput(); 
        void commandPurpose(string input); 
        void printMenu(); 
}; 