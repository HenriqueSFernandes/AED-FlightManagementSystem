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
    Menu menu(system);
    menu.start();
    cout<<"END"<<endl;

    return 0;
}
