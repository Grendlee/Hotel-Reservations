// Rectangle.cpp file
// Description: This class models a rectangle ...
// Author: Grantley
// Creation date: May 10, 2023
#include "Customer.h"

using namespace std;

//Default constructor
Customer::Customer() : id("ShouldNotHappen"), requestedBeds(-1)
{
    
}

//constructor
Customer::Customer(const string i, const int rB) 
{
    id = i;
    requestedBeds = rB;
}

//destructor
Customer::~Customer()
{

}

string Customer::getId()
{
    return id;
}

int Customer::getRequestedBeds()
{
    return requestedBeds;
}

//copy
Customer::Customer(const Customer& c)
{
    id = c.id;
    requestedBeds = c.requestedBeds;
}
