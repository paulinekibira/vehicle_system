#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string make;
    string model;
    int year;

public:
    Vehicle(string m, string mod, int y) : make(m), model(mod), year(y) {}

    virtual ~Vehicle() {}
    virtual double calculateRentalCost(int days) = 0;
    void displayInfo() {
        cout << "Make: " << make << ", Model: " << model << ", Year: " << year;
    }
};
