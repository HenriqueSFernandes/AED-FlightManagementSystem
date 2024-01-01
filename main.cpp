#include <iostream>
#include "src/ManagementSystem.h"
#include "src/Menu.h"

using namespace std;

int main() {
    ManagementSystem system;
    cout << "Loading airlines\n";
    system.readAirlines();
    cout << "Loading airports\n";
    system.readAirports();
    cout << "Loading flights\n";
    system.readFlights();
    vector<Vertex<Airport> *> source;
    vector<Vertex<Airport> *> target;
    vector<Vertex<Airport> *> filteredAirports;
    set < Airline > filteredAirlines;
    source.push_back(system.getAirportNetwork().findVertex(Airport("OPO", "", "", "", 0, 0)));
    filteredAirports.push_back(system.getAirportNetwork().findVertex(Airport("YYZ", "", "", "", 0, 0)));
    target.push_back(system.getAirportNetwork().findVertex(Airport("SRV", "", "", "", 0, 0)));

    vector<Airport> trip = system.findBestFlight(source, target, filteredAirports, filteredAirlines);
    for (auto i: trip) {
        cout << i.getCode() << " ";
    }
    cout << endl;
    Menu menu(system);
    menu.start();
    return 0;
}
