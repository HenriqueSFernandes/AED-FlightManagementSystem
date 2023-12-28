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
    for (auto i: system.cities) {
        cout << "\n" << i.first << ": ";
        for (auto j: i.second) {
            cout << j << " ";
        }
    }
    Menu menu(system);
    menu.start();
    return 0;
}
