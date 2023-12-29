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
    set<Vertex<Airport> *> source;
    set<Vertex<Airport> *> target;
    source.insert(system.getAirportNetwork().findVertex(Airport("ZLT", "", "", "", 0, 0)));
    source.insert(system.getAirportNetwork().findVertex(Airport("OPO", "", "", "", 0, 0)));


    target.insert(system.getAirportNetwork().findVertex(Airport("SRV", "", "", "", 0, 0)));

    vector<vector<Airport>> paths = system.findBestFlights(source, target);
    for (auto i: paths) {
        cout << "Trip:\n";
        for (auto j: i) {
            cout << j.getCode() << " ";
        }
    }

    cout << endl;
    Menu menu(system);
    menu.start();
    return 0;
}
