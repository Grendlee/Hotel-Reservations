// Circle.h file
// Description: This class models a circle
// Author: Grantley
// Creation date: Mayth 10th, 2023
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
using namespace std;
class Customer {
    private: 
        string id;
        int requestedBeds;
    public: 

        //new uses this
        Customer(); //the default constructor has no parameters.
        
        //constructor
        Customer(string id, int requestedBeds);

        //delete
        //destructor method
        ~Customer();

        //during function call
        //copy constructor
        Customer(const Customer&);

        string getId();

        int getRequestedBeds();

};

#endif