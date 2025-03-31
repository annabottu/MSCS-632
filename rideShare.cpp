#define _ENABLE_EXTENDED_ALIGNED_STORAGE
#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class Rider;
class Driver;

class Ride {
public:
    string rideId;
    shared_ptr<Rider> rider;
    shared_ptr<Driver> driver;
    string pickupLocation;
    string dropoffLocation;
    double distance;
    double fare;

    Ride(string rideId, shared_ptr<Rider> rider, shared_ptr<Driver> driver,
         const string& pickupLocation, const string& dropoffLocation, double fare)
        : rideId(rideId), rider(rider), driver(driver),
          pickupLocation(pickupLocation), dropoffLocation(dropoffLocation), fare(fare) {
        distance = calculateDistance();
    }

    virtual double calculateDistance() {
        return (pickupLocation.length() + dropoffLocation.length()) / 10.0;
    }

    virtual double calculateFare() {
        return 3.0 + distance * 3.0;
    }

    virtual void rideDetails();

    virtual ~Ride() {}
};

class User {
public:
    string userId;
    string name;
    string phone;

    User(string userId, string name, string phone)
        : userId(userId), name(name), phone(phone) {}
};

class Vehicle {
public:
    string model;
    int year;
    string vehicleType;

    Vehicle(const string& model, int year, const string& vehicleType)
        : model(model), year(year), vehicleType(vehicleType) {}
};

class Driver : public User {
private:
    vector<shared_ptr<Ride> > assignedRides;

public:
    shared_ptr<Vehicle> vehicle;
    string licensePlate;
    bool available;

    Driver(string userId, string name, string phone, shared_ptr<Vehicle> vehicle, const string& licensePlate)
        : User(userId, name, phone), vehicle(vehicle), licensePlate(licensePlate), available(true) {}

    void addRide(shared_ptr<Ride> ride) {
        assignedRides.push_back(ride);
    }

    void getDriverInfo() {
        cout << "Driver ID: " << userId << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Vehicle: " << vehicle->model << " (" << vehicle->vehicleType << ")" << endl;
        cout << "License Plate: " << licensePlate << endl;
        cout << "Rides Completed: " << assignedRides.size() << endl;
    }
};

class Rider : public User {
private:
    vector<shared_ptr<Ride> > requestedRides;

public:
    string paymentMethod;
    vector<shared_ptr<Ride> > rideHistory;

    Rider(string userId, string name, string phone, const string& paymentMethod)
        : User(userId, name, phone), paymentMethod(paymentMethod) {}

    void requestRide(shared_ptr<Ride> ride) {
        requestedRides.push_back(ride);
    }

    void viewRides() {
        cout << "\nRide History for " << name << ":" << endl;
        if (rideHistory.empty()) {
            cout << "No rides completed yet." << endl;
        } else {
            for (size_t i = 0; i < rideHistory.size(); ++i) {
                cout << "\nRide " << i + 1 << ":" << endl;
                rideHistory[i]->rideDetails();
            }
        }
    }
};
/*This is the base class Ride that holds the following details such as: rideID, pickupLocation, dropoffLocation, distance, and fare.*/
void Ride::rideDetails() {
    cout << "Ride ID: " << rideId << endl;
    cout << "Pickup: " << pickupLocation << endl;
    cout << "Dropoff: " << dropoffLocation << endl;
    cout << "Distance: " << distance << " units" << endl;
    cout << "Fare: $" << fare << endl;
    cout << "Driver: " << driver->name << endl;
    cout << "Rider: " << rider->name << endl;
}

/*this is a derived class from Ride*/
class StandardRide : public Ride {
public:
    StandardRide(string rideId, shared_ptr<Rider> rider, shared_ptr<Driver> driver,
                 const string& pickupLocation, const string& dropoffLocation, double fare)
        : Ride(rideId, rider, driver, pickupLocation, dropoffLocation, fare) {}
    /*overrides the fare method*/
    double calculateFare()  {
        return 3.0 + distance * 2.5;
    }
};
/*this is a derived class from Ride*/
class PremiumRide : public Ride {
public:
    PremiumRide(string rideId, shared_ptr<Rider> rider, shared_ptr<Driver> driver,
                const string& pickupLocation, const string& dropoffLocation, double fare)
        : Ride(rideId, rider, driver, pickupLocation, dropoffLocation, fare) {}
    /*overrides the fare method*/
    double calculateFare() {
        return 5.0 + distance * 4.0;
    }
};
