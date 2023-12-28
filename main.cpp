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
    auto viires = system.maxTripWithSourceDest();
    for(auto i : viires.first){
        cout<<"Source: " << i.first.getCode() << " - " << i.first.getName() << endl;
        cout<<"Target: " << i.second.getCode() << " - " << i.second.getName() << endl << endl;
    }
    cout<<"Stops: " << viires.second<<endl;
    Menu menu(system);
    menu.start();
    return 0;
}
