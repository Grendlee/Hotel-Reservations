// Hotel.cpp file
// Descriptions: This class reads customer orders and fufills them if possible
// Author: Grantley
// Creation date: June 10th, 2023

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Room.h"
#include "Customer.h"
using namespace std;


int oneBedsLeft = 100;
int twoBedsLeft = 50;
int threeBedsLeft = 30;

int customersServedToday = 0;
int customersRejectedToday = 0;
int customersCheckOutToday = 0;
int newRoomsAvailable = 0;

string globalDate = "-1/-1/-1";

//speghetti code flag to assign the first date in the log as the start date of hotel
bool firstDateFound = false;


class Queue {
    public:
        Room *r;
        Queue *next;
        Queue *prev;
};

//returns  if leap year
bool isLeapYear(int year) 
{
    if (year % 4 == 0) 
    {
        if (year % 100 == 0) 
        {
            if (year % 400 == 0) 
            {
                return true;
            }
            return false;
        } 
        return true;
    }

    return false;
}

//returns date after x days
string dateAfterXDays(const string checkInDate, int xDays) {
    
    //parse string
    istringstream iss(checkInDate);
    string day, month, year;
    getline(iss, day, '/');
    getline(iss, month, '/');
    getline(iss, year);

    //turn string to int
    int checkInMonth = stoi(month);
    int checkInDay = stoi(day);
    int checkInYear = stoi(year);

    // Add the number of days of stay to the check-in date
    int checkOutDay = checkInDay +  xDays;
    int checkOutMonth = checkInMonth;
    int checkOutYear = checkInYear;

    int maxDaysInMonth;
    const int daysInMonth[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool finishedConvertingDate = false;
    while (!finishedConvertingDate && checkOutDay > 28) //loop to ensure checkOutDay is an actual date in the calender
    {

        //check if leap year
        if (checkOutMonth == 2 && isLeapYear(checkOutYear)) 
        {
            maxDaysInMonth = 29;
        } 
        else 
        {
            maxDaysInMonth = daysInMonth[checkOutMonth];
        }

        //check if need to increment month
        if (checkOutDay > maxDaysInMonth) 
        {
            checkOutDay = checkOutDay - maxDaysInMonth;
            checkOutMonth++;
            
            //check if need to increment year
            if (checkOutMonth > 12) {
                checkOutMonth = 1;
                checkOutYear++;
            }
        }
        else
        {
            finishedConvertingDate = true;
        }
        //continue loop if checkOutDay is > than max days in a month
    }

    // Build the check-out date string
    string checkOutDate = "";

    checkOutDate += to_string(checkOutDay);
    checkOutDate += '/';
    checkOutDate += to_string(checkOutMonth);
    checkOutDate += '/';
    checkOutDate += to_string(checkOutYear);

    return checkOutDate;
}

//remove slashes from date so text files can be created
string removeSlashesAndReplaceWithUnderScore(string date)
{
    for(int i = 0; i < date.length(); i++)
    {
        if(date[i] == '/')
        {
            date[i] = '_';
        }
    }
    return date;
}

//returns if hotel can serve customer in the form of "(numberOfOneBeds),(numberOfTwoBeds),(numberOfThreeBeds)"
string ableToServeCustomer(int requestedBeds)
{

    //simple case
    if(requestedBeds == 1 &&  oneBedsLeft >= 1)
    {
        oneBedsLeft--;
        return "1,0,0";
    }
    else if(requestedBeds == 2 &&  twoBedsLeft >= 1)//simple case
    {
        twoBedsLeft--;
        return "0,1,0";
    }
    else if(requestedBeds == 3 &&  threeBedsLeft >= 1)//simple case
    {
        threeBedsLeft--;
        return "0,0,1";
    }
    else//start of a needed combination of rooms to satisfy customer
    {

        string order = "";
        
        int oneBeds;
        int twoBeds;
        int threeBeds;

        //fit as many one beds as possible
        for(oneBeds = 0; oneBedsLeft != 0 && oneBeds < oneBedsLeft && oneBeds < requestedBeds; oneBeds++)
        {
        }

        if(oneBeds == requestedBeds) //return string if no need for additional rooms
        {
            oneBedsLeft -= oneBeds;
            string s = to_string(oneBeds);
            s += ",0,0";

            return s; 
        }

        //fit as many two beds as possible
        for(twoBeds = 0; twoBedsLeft != 0 && twoBeds < twoBedsLeft && oneBeds + (twoBeds*2) < requestedBeds; twoBeds++)
        {
        }

        if(oneBeds + (twoBeds*2) >= requestedBeds)//return string if no need for additional rooms
        {
            if(twoBeds*2 >= requestedBeds) //check to see if algo gave too many rooms
            {
                oneBeds = 0;
                
            }

            oneBedsLeft -= oneBeds;
            twoBedsLeft -= twoBeds;
            string s = to_string(oneBeds);
            s += ",";
            s += to_string(twoBeds);
            s += ",0";

            return s; 
        }

        //fit as many three beds as possible
        for(threeBeds = 0; threeBedsLeft != 0 && threeBeds < threeBedsLeft && oneBeds + (twoBeds*2) + (threeBeds*3) < requestedBeds; threeBeds++)
        {
        }

        if(oneBeds + (twoBeds*2) + (threeBeds*3) >= requestedBeds)//return string if no need for additional rooms
        {
            if(threeBeds*3 >= requestedBeds)//check to see if algo gave too many rooms
            {
                oneBeds = 0;
                twoBeds = 0;
            }

            if(threeBeds*3 + (twoBeds*2) >= requestedBeds)//check to see if algo gave too many rooms
            {
                oneBeds = 0;
            }

            if(threeBeds*3 + (twoBeds*2)  + oneBeds-1>= requestedBeds && oneBeds > 0)//check to see if algo gave too many rooms
            {
                oneBeds--;
            }

            if(threeBeds*3 + (twoBeds*2)  + oneBeds-1>= requestedBeds && oneBeds > 0)//check to see if algo gave too many rooms
            {
                oneBeds--;
            }

            //update beds left
            oneBedsLeft -= oneBeds;
            twoBedsLeft -= twoBeds;
            threeBedsLeft -= threeBeds;
            
            //return the combinations in the form of "(numberOfOneBeds),(numberOfTwoBeds),(numberOfThreeBeds)""
            string s = to_string(oneBeds);
            s += ",";
            s += to_string(twoBeds);
            s += ",";
            s += to_string(threeBeds);

            return s; 
        }
    }
    
    return "No Rooms Available to Satisfy Customer"; //could not find a room combo for customer
}

//check out the customers that have a checkout date the same as global date
void checkOutCustomers(Queue*& head) 
{
    Queue* curr = head;
    while (curr != nullptr) //iterate to the end of the list
    {
        if (curr->r->getOutDate() == globalDate) 
        {

            Queue* temp = curr;

            //check which room type
            if(curr->r->getBeds()== 1)
            {
                oneBedsLeft++;
            }
            else if(curr->r->getBeds() == 2)
            {
                twoBedsLeft++;
            }
            else if(curr->r->getBeds() == 3)
            {
                threeBedsLeft++;
            }
            newRoomsAvailable++;
            //connect nodes so that temp is a dangling pointer
            if (curr->prev != nullptr) 
            {
                curr->prev->next = curr->next;
            }

            if (curr->next != nullptr) 
            {
                curr->next->prev = curr->prev;
            }

            //check if curr == head, move head, then delete
            if (curr == head) 
            {
                head = curr->next;
            }

            curr = curr->next;
            //delete customer pointer

            //check if no more nodes after and check if next room still has customer of same id
            if(temp->next != nullptr && temp->next->r->getCustomer() == temp->r->getCustomer())
            {
                
            }
            else //only delete if all previous rooms have been checked out to avoid deleting cust twice
            {
                temp->r->checkoutCustomer();
            }

            //delete room pointer
            if(temp->r != nullptr)
            {
                delete temp->r;
                temp->r = nullptr;
            }
            //delete queue node
            if(temp!= nullptr)
            {
                delete temp;
                temp = nullptr;
            }
            
        } 
        else 
        {
            //continue search
            curr = curr->next;
        }
    }
}

int main() {

    int printNumber = 0;
    string errorFile = "CustomersRejected.txt";
    int customersServedSinceInception = 0;
    int customersRejectedSinceInception = 0;
    int numberOfCustomerRequests = 0;

    Queue* head = nullptr;
    ifstream file("Customers.txt"); // Assuming the file is named "data.txt"

    if (!file) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    getline(file, line); //get rid of first line


    string checkInDate, customerId, requestedBeds, days, checkOutDate;
    string outputFileName;

    //read the rest of the file
    while (getline(file, line)) {
        numberOfCustomerRequests++;
        istringstream iss(line);

        //parse up to char value
        getline(iss >> ws,checkInDate,',');
        getline(iss >> ws,customerId,',');
        getline(iss >> ws,requestedBeds,',');
        getline(iss >> ws,days,' ');

        //used to assign first date where customer checks-in to the globalDate of the hotel. ie the start date of the hotel
        if(!firstDateFound)
        {
            globalDate = checkInDate;
            firstDateFound = true;
        }

        while(checkInDate != globalDate)//done with the current day, perform maintenence tasks, increment globalDate by one
        {
            

            outputFileName = to_string(printNumber) + "_DATE__" + removeSlashesAndReplaceWithUnderScore(globalDate) + "__LOG.txt";
            
            printNumber++;

            ofstream outputFile(outputFileName); 

            if (outputFile.is_open()) //file opened
            { 

                outputFile << "------------------------------------------------"  << "\n";
                outputFile << "DATE:" << globalDate  << "\n";
                outputFile << "Customers Served: " << customersServedToday  << "\n";
                customersServedToday = 0;
                outputFile << "Customers Rejected: " << customersRejectedToday  << "\n";
                customersRejectedToday = 0;
                //checkout customers with checkout date of today

                checkOutCustomers(head);

                outputFile << "New Rooms Available: " << newRoomsAvailable  << "\n";
                newRoomsAvailable = 0;
                outputFile << "One beds left: " << oneBedsLeft  << "\n";
                outputFile << "Two beds left: " << twoBedsLeft  << "\n";
                outputFile << "Three beds left: " << threeBedsLeft  << "\n";
                outputFile << "Customers rejected since inception: " << customersRejectedSinceInception << "\n";
                outputFile << "Customers served since inception: " << customersServedSinceInception << "\n";
                outputFile << "Number of customer requests since inception: " << numberOfCustomerRequests << "\n";

                outputFile << "------------------------------------------------"  << "\n";

                outputFile.close();//close the file

            } 
            else 
            {
                cout << "Error in opening file for date:" << globalDate << endl;
            }

            globalDate = dateAfterXDays(globalDate, 1);
        }
            
        //global date == checkInDate, all logs have been printed prior to this date
        

        checkOutDate = dateAfterXDays(checkInDate, stoi(days));
        //convert from date and assign to room class.
        Customer *cust = new Customer(customerId, stoi(requestedBeds));
        string customerRoomAllocation = ableToServeCustomer(cust->getRequestedBeds());

        //check if can serve customer
        if(customerRoomAllocation == "No Rooms Available to Satisfy Customer")
        {
            //reject customer
            customersRejectedToday++;
            customersRejectedSinceInception++;
            ofstream outputFile1(errorFile, std::ios::app); //open file in append mode

            if (outputFile1.is_open()) //file opened
            { 
                outputFile1 << "------------------------------------------------"  << "\n";
                outputFile1 << "Date: " << globalDate << endl << "Customer: " << cust->getId() << endl << "Requested beds: " << requestedBeds << endl << "The hotel currently does not have enough beds to satisfy this order." << endl;
                outputFile1 << "------------------------------------------------"  << "\n";

                outputFile1.close();
            } 
            else 
            {
                cout << "Error in opening file for date:" << globalDate << endl;
            }
            delete cust;
            









        }
        else//able to serve
        {
            
            customersServedToday++;
            customersServedSinceInception++;
            string oneBedsToServe;
            string twoBedsToServe;
            string threeBedsToServe;

            //read in string
            istringstream iss(customerRoomAllocation);
            // cout<< "customerRoomAllocation " << customerRoomAllocation << endl;
            getline(iss >> ws,oneBedsToServe,',');
            getline(iss >> ws,twoBedsToServe,',');
            getline(iss >> ws,threeBedsToServe,' ');

            int oneBedsToServeINT = stoi(oneBedsToServe);
            int twoBedsToServeINT = stoi(twoBedsToServe);
            int threeBedsToServeINT = stoi(threeBedsToServe);

            //add to list the number of one beds
            for(int i = 1; i <= oneBedsToServeINT; i++)
            {

                Room* room = new Room(cust, checkInDate, checkOutDate, 1);
                Queue* occupiedRoom = new Queue();

                //if no nodes in queue
                if(head == nullptr)
                {
                    occupiedRoom->r = room;
                    occupiedRoom->next = nullptr;
                    occupiedRoom->prev = nullptr;
                    head = occupiedRoom;
                }
                else //enqueue and connect to head
                {
                    occupiedRoom->r = room;
                    occupiedRoom->next = head;
                    head->prev = occupiedRoom;
                    occupiedRoom->prev = nullptr;
                    head = occupiedRoom;
                }
            }

            //add to list the number of two beds
            for(int i = 1; i <= twoBedsToServeINT; i++)
            {
                Room* room = new Room(cust, checkInDate, checkOutDate, 2);
                Queue* occupiedRoom = new Queue();
                //if no nodes in queue
                if(head == nullptr)
                {
                    occupiedRoom->r = room;
                    occupiedRoom->next = nullptr;
                    occupiedRoom->prev = nullptr;
                    head = occupiedRoom;
                }
                else
                {//enqueue and connect to head
                    occupiedRoom->r = room;
                    occupiedRoom->next = head;
                    head->prev = occupiedRoom;
                    occupiedRoom->prev = nullptr;
                    head = occupiedRoom;
                }
            }

            //add to list the number of three beds
            for(int i = 1; i <= threeBedsToServeINT; i++)
            {
                Room* room = new Room(cust, checkInDate, checkOutDate, 3);
                Queue* occupiedRoom = new Queue();

                 //if no nodes in queue
                if(head == nullptr)
                {
                    occupiedRoom->r = room;
                    occupiedRoom->next = nullptr;
                    occupiedRoom->prev = nullptr;
                    head = occupiedRoom;
                }
                else
                {//enqueue and connect to head
                    occupiedRoom->r = room;
                    occupiedRoom->next = head;
                    head->prev = occupiedRoom;
                    occupiedRoom->prev = nullptr;
                    head = occupiedRoom;
                }
            }
        }
    }


    //done with all customers in log file

    //log last days activities
    outputFileName = to_string(printNumber) + "_DATE__" + removeSlashesAndReplaceWithUnderScore(globalDate) + "__LOG.txt";
    printNumber++;

    ofstream outputFile(outputFileName); 

    if (outputFile.is_open()) //file opened
    { 
        outputFile << "------------------------------------------------"  << "\n";
        outputFile << "DATE:" << globalDate  << "\n";
        outputFile << "Customers Served: " << customersServedToday  << "\n";
        customersServedToday = 0;
        outputFile << "Customers Rejected: " << customersRejectedToday  << "\n";
        customersRejectedToday = 0;
        //checkout customers with checkout date of today
        checkOutCustomers(head);

        outputFile << "New Rooms Available: " << newRoomsAvailable  << "\n";
        newRoomsAvailable = 0;
        outputFile << "One beds left: " << oneBedsLeft  << "\n";
        outputFile << "Two beds left: " << twoBedsLeft  << "\n";
        outputFile << "Three beds left: " << threeBedsLeft  << "\n";
        outputFile << "Customers rejected since inception: " << customersRejectedSinceInception << "\n";
        outputFile << "Customers served since inception: " << customersServedSinceInception << "\n";
        outputFile << "------------------------------------------------"  << "\n";

        outputFile.close();//close the file
    } 
    else 
    {
        cout << "Error in opening file for date:" << globalDate << endl;
    }


    globalDate = dateAfterXDays(globalDate, 1);

    

    //print remainder dates so that queue is empty
    while(head != nullptr)
    {
        //log last days activities
        outputFileName = to_string(printNumber) + "_DATE__" + removeSlashesAndReplaceWithUnderScore(globalDate) + "__LOG.txt";
        printNumber++;

        ofstream outputFile(outputFileName);

        if (outputFile.is_open()) //file opened
        { 
            outputFile << "------------------------------------------------"  << "\n";
            outputFile << "DATE:" << globalDate  << "\n";
            outputFile << "Customers Served: " << customersServedToday  << "\n";
            customersServedToday = 0;
            outputFile << "Customers Rejected: " << customersRejectedToday  << "\n";
            customersRejectedToday = 0;
            //checkout customers with checkout date of today
            checkOutCustomers(head);

            outputFile << "New Rooms Available: " << newRoomsAvailable  << "\n";
            newRoomsAvailable = 0;
            outputFile << "One beds left: " << oneBedsLeft  << "\n";
            outputFile << "Two beds left: " << twoBedsLeft  << "\n";
            outputFile << "Three beds left: " << threeBedsLeft  << "\n";
            outputFile << "Customers rejected since inception: " << customersRejectedSinceInception << "\n";
            outputFile << "Customers served since inception: " << customersServedSinceInception << "\n";
            outputFile << "Number of customer requests since inception: " << numberOfCustomerRequests << "\n";
            outputFile << "------------------------------------------------"  << "\n";

            outputFile.close();//close the file
        } 
        else 
        {
            cout << "Error in opening file for date:" << globalDate << endl;
        }


        globalDate = dateAfterXDays(globalDate, 1);
    }












    cout << "Done. All logs in directory" << endl;

    
    file.close();
    

    return 0;
}