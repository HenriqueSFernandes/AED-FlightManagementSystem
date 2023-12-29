#include <iostream>
#include <cmath>
#include "src/ManagementSystem.h"
#include "src/Menu.h"
#include "/home/jose/Documents/proj2aed/aed-flights/Image/Script.hpp"
using namespace std;

int main() {
    prog::Script script= prog::Script("/home/jose/Documents/proj2aed/aed-flights/Image/input/worldmap.png");

    ManagementSystem system;
    cout << "Loading airlines\n";
    system.readAirlines();
    cout << "Loading airports\n";
    system.readAirports();
    cout << "Loading flights\n";
    system.readFlights();
    script.open();

    for( auto airport : system.getAirports()){
        int x=round(airport.getLongitude()*1.7621+343.4);
        int y=0;
        if( airport.getLatitude()<0){
            y=round(airport.getLatitude()*(-1.909)+258.71);
        }else{
            if(airport.getLatitude()>60){
                y=round(airport.getLatitude()*(-2.209)+268.71);
            }else{
                y=round(-1.909*airport.getLatitude()+261.71);
            }

        }

        script.fill(x,y,3,3,255,0,0);

    }
    script.save();
    cout<<"END"<<endl;
    /*
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
    menu.start();*/
    return 0;
}
