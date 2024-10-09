#include <string>
#include "Room.h"

using namespace std;


Room::Room() : cust(nullptr), inDate("-1/-1/-1"), outDate("-1/-1/-1"), beds(-1)
{

}

//constructor
Room::Room(Customer* c, string inDate, string outDate, int beds) : cust(c), inDate(inDate), outDate(outDate), beds(beds)
{
    
}

//delete
//destructor method
Room::~Room()
{

}

//during function call
//copy constructor
Room::Room(const Room& r)
{
    cust = r.cust;
    inDate = r.inDate;
    outDate = r.outDate;
    beds = r.beds;
}


string Room::getInDate()
{
    return inDate;
}

string Room::getOutDate()
{
    return outDate;
}

int Room::getBeds()
{
    return beds;
}

string Room::getCustomer()
{
    return cust->getId();
}

void Room::checkoutCustomer(){
   if(cust != nullptr)
   {
        delete cust; 
        cust = nullptr;
   }
}

