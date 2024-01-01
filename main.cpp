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

    /*
    for( auto airport : system.getAirports()){
        int x=round(airport.getLongitude()*1.7621+343.4);
        int y=  260 -round(1.23*(450/(2*M_PI)*log2(tan(M_PI/4+airport.getLatitude()*M_PI*0.4/180))));

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


       // script.fill(x,y,3,3,255,0,0);

    }
    Airport airport1 = *system.getAirports().find(Airport("JFK", "", "", "", 0, 0));
    Airport airport2 = *system.getAirports().find(Airport("MEB", "", "", "", 0, 0));

    double currentLat=airport1.getLatitude();
    double currentLong=airport1.getLongitude();
    double targetLat=airport2.getLatitude();
    double targetLong=airport2.getLongitude();
    while(abs(targetLat-currentLat)>0.01 or abs(targetLong-currentLong)>0.01){
        double deltaX=(targetLong-currentLong)/360;
        currentLong+=deltaX;
        double deltay=(targetLat-currentLat)/180;
        currentLat+=deltay;
        int x = round(currentLong* 1.7621 + 343.4);
        int y = 260 - round(1.23 * (450 / (2 * M_PI) * log2(tan(M_PI / 4 + currentLat* M_PI * 0.4 / 180))));
        script.fill(x, y, 2, 2, 255, 0, 0);
    }

    script.save();
    cout<<"END"<<endl;*/
    Airport airport1 = *system.getAirports().find(Airport("OPO", "", "", "", 0, 0));
    Airport airport2 = *system.getAirports().find(Airport("YYZ", "", "", "", 0, 0));
    Airport airport3 = *system.getAirports().find(Airport("GRU", "", "", "", 0, 0));




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
