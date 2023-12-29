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
    set < Airport > source;
    set < Airport > target;
    source.insert(*system.getAirports().find(Airport("ZLT", "", "", "", 0, 0)));
    source.insert(*system.getAirports().find(Airport("OPO", "", "", "", 0, 0)));

    target.insert(*system.getAirports().find(Airport("SRV", "", "", "", 0, 0)));
    system.findBestFlights(source, target);
    Menu menu(system);
    menu.start();
    return 0;
}
