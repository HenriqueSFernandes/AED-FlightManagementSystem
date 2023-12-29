#include <iostream>
#include "src/ManagementSystem.h"
#include "src/Menu.h"
#include "/home/jose/Documents/proj2aed/aed-flights/Image/Script.hpp"
using namespace std;

int main() {
    prog::Script script= prog::Script("/home/jose/Documents/proj2aed/aed-flights/Image/input/fcul.png");
    script.open();
    script.fill(0,0,200,200,12,12,12);
    script.save();
    ManagementSystem system;
    cout << "Loading airlines\n";
    system.readAirlines();
    cout << "Loading airports\n";
    system.readAirports();
    cout << "Loading flights\n";
    system.readFlights();
    set < Airport > source;
    set < Airport > target;
    source.insert(*system.getAirports().find(Airport("ZLT", "", "", "", 0, 0)));
    source.insert(*system.getAirports().find(Airport("OPO", "", "", "", 0, 0)));

    target.insert(*system.getAirports().find(Airport("SRV", "", "", "", 0, 0)));
    target.insert(*system.getAirports().find(Airport("JFK", "", "", "", 0, 0)));
    target.insert(*system.getAirports().find(Airport("CDG", "", "", "", 0, 0)));
    vector<vector<Airport>> paths = system.findBestFlights(source, target);
    for (auto i : paths){
        cout << "Trip:\n";
        for (auto j : i){
            cout << j.getCode() << " ";
        }
    }

    cout << endl;
    Menu menu(system);
    menu.start();
    return 0;
}
