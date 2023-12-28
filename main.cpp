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
    set<Airport> a;
    set<string> b;
    set<string> c;
    system.airportDetails("ZZZ");
    Menu menu(system);
    menu.start();
    return 0;
}
