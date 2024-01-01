#include <iostream>
#include <cmath>
#include "src/ManagementSystem.h"
#include "src/Menu.h"
#include "src/Image/Script.hpp"

using namespace std;

int main() {

    ManagementSystem system;
    cout << "Loading airlines\n";
    system.readAirlines();
    cout << "Loading airports\n";
    system.readAirports();
    cout << "Loading flights\n";
    system.readFlights();
    Airport airport1 = system.getAirportNetwork().findVertex(Airport("OPO", "", "", "", 0, 0))->getInfo();
    Airport airport2 = system.getAirportNetwork().findVertex(Airport("YYZ", "", "", "", 0, 0))->getInfo();
    Airport airport3 = system.getAirportNetwork().findVertex(Airport("GRU", "", "", "", 0, 0))->getInfo();
  
    vector<Airport> UWU;
    UWU.push_back(airport1);
    UWU.push_back(airport2);
    UWU.push_back(airport3);

    set<Airport> k;
    k.insert(airport2);
    k.insert(airport3);
    k.insert(airport1);
    system.printAirports(k,"src/Image/output/okokisaisok.png");

    system.printComposedPath(UWU,"src/Image/output/UWUFES.png");

    Menu menu(system);
    menu.start();
    cout<<"END"<<endl;

    return 0;
}
