#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string make;
    string model;
    int year;

public:
    Vehicle(string m, string mod, int y)
        : make(m), model(mod), year(y) {}

    virtual ~Vehicle() {}

    virtual double calculateRentalCost(int days) = 0;

    void displayInfo() {
        cout << "Make: " << make
             << ", Model: " << model
             << ", Year: " << year;
    }
};

class Car : public Vehicle {
private:
    int numDoors;
    bool isLuxury;

public:
    Car(string m, string mod, int y, int doors, bool luxury)
        : Vehicle(m, mod, y), numDoors(doors), isLuxury(luxury) {}

    double calculateRentalCost(int days) override {
        double baseRate = isLuxury ? 80.0 : 50.0;
        return baseRate * days;
    }

    void displayCarInfo() {
        displayInfo();
        cout << ", Doors: " << numDoors
             << ", Luxury: " << (isLuxury ? "Yes" : "No") << endl;
    }
};

class SUV : public Vehicle {
private:
    int seatingCapacity;
    bool hasFourWheelDrive;

public:
    SUV(string m, string mod, int y, int seats, bool fourWD)
        : Vehicle(m, mod, y), seatingCapacity(seats), hasFourWheelDrive(fourWD) {}

    double calculateRentalCost(int days) override {
        double baseRate = hasFourWheelDrive ? 70.0 : 60.0;
        return baseRate * days;
    }

    void displaySUVInfo() {
        displayInfo();
        cout << ", Seats: " << seatingCapacity
             << ", 4WD: " << (hasFourWheelDrive ? "Yes" : "No") << endl;
    }
};

class Truck : public Vehicle {
private:
    double cargoCapacity;
    bool isCommercial;

public:
    Truck(string m, string mod, int y, double capacity, bool commercial)
        : Vehicle(m, mod, y), cargoCapacity(capacity), isCommercial(commercial) {}

    double calculateRentalCost(int days) override {
        double baseRate = isCommercial ? 100.0 : 75.0;
        return baseRate * days;
    }

    void displayTruckInfo() {
        displayInfo();
        cout << ", Cargo: " << cargoCapacity << " tons"
             << ", Commercial: " << (isCommercial ? "Yes" : "No") << endl;
    }
};

int main() {
    Car car1("Toyota", "Corolla", 2022, 4, false);
    SUV suv1("Ford", "Explorer", 2021, 7, true);
    Truck truck1("Isuzu", "N-Series", 2020, 5.0, true);

    int days = 3;

    cout << "----- Car Rental -----" << endl;
    car1.displayCarInfo();
    cout << "Rental Cost for " << days << " days: $"
         << car1.calculateRentalCost(days) << endl << endl;

    cout << "----- SUV Rental -----" << endl;
    suv1.displaySUVInfo();
    cout << "Rental Cost for " << days << " days: $"
         << suv1.calculateRentalCost(days) << endl << endl;

    cout << "----- Truck Rental -----" << endl;
    truck1.displayTruckInfo();
    cout << "Rental Cost for " << days << " days: $"
         << truck1.calculateRentalCost(days) << endl;

    return 0;
}
