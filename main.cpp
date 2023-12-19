#include <iostream>
#include "src/ManagementSystem.h"

using namespace std;

int main() {
    ManagementSystem system;
    system.readAirlines();
    system.readAirports();
    system.readFlights();
    cout << "-----Airlines-----\n";
    for (auto airline: system.getAirlines()) {
        cout << "Code: " << airline.getCode() << " Name: " << airline.getName() << " Callsign: " << airline.getCallsign()
             << " Country: " << airline.getCountry() << "\n";
    }
    cout << "-----Airports-----\n";
    for (auto airport: system.getAirportsMap()) {
        cout << "Code: " << airport.getCode() << " City: " << airport.getCity()
             << " Country: " << airport.getCountry() << "\n";
    }
    cout << "-----Flights-----\n";
    for (auto flight: system.getFlights()) {
        cout << "Origin: " << flight.getSource() << " Destination: " << flight.getTarget() << endl;
        for (auto airline: flight.getAirlines()) {
            cout << "Code: " << airline.getCode() << " Name: " << airline.getName() << " Callsign: "
                 << airline.getCallsign() << " Country: " << airline.getCountry() << "\n";
        }
    }
    return 0;
}
