# Hotel-Reservations


Hotel reservations is a program that simulates a hotel room management system. The program takes customer orders from a text file and assigns them rooms when available. A doubly linked list is used as its data structure. Daily logs are generated to indicate available rooms, customer check-in and check-outs based on their reservation requests.

# How to Compile

To compile all the source files, use the following command:

```clang++ -std=c++11 -stdlib=libc++ Hotel.cpp Room.cpp Customer.cpp -o HotelManagement```

# How to Run

```./HotelManagement```

# File Structure


## Hotel.cpp

- Implementation of hotel reservation system

## Room.cpp and Room.h

- Models a Room class

## Customers.cpp and Customers.h

- Models a Customer that requests duration of stay and number of beds

## Customers.txt

- Input file containing list of customer reservations

## CustomersRejected.txt

- Output file that logs customer orders that could not be fulfilled due to room shortages

## Generated Daily Logs

- Each days activity
