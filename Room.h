

// #ifndef ROOM_H
// #define ROOM_H

#include <string>
#include "Customer.h"

using namespace std;

class Room {
    private: 
        Customer* cust;
        string inDate;
        string outDate;
        int beds;
    public: 

        //new uses this
        Room(); //the default constructor has no parameters.
        
        //constructor
        Room(Customer* c, string iD, string oD, int b);

        //delete
        //destructor method
        ~Room();

        //during function call
        //copy constructor
        Room(const Room&);

        string getInDate();

        string getOutDate();

        int getBeds();

        string getCustomer();

        void checkoutCustomer();

};

// #endif