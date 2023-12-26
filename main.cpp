#include <iostream>
#include "src/ManagementSystem.h"

using namespace std;

int main() {
    ManagementSystem system;
    cout << "Loading airlines\n";
    system.readAirlines();
    cout << "Loading airports\n";
    system.readAirports();
    cout << "Loading flights\n";
    system.readFlights();
    cout << "****************************************\n" << "*               Airlines               *\n"
         << "****************************************\n";
    for (const Airline &airline: system.getAirlines()) {
        cout << airline << endl;
    }
    cout << "****************************************\n" << "*               Airports               *\n"
         << "****************************************\n";

    for (const Airport &airport: system.getAirports()) {
        cout << airport << endl;
    }
    cout << "****************************************\n" << "*               Flights                *\n"
         << "****************************************\n";

    for (const Flight &flight: system.getFlights()) {
        cout << flight << endl;
    }
    for( auto vertex : system.getAirportNetwork().getVertexSet()){
        cout<< vertex->getInfo().getCode()<<"goes to "<<vertex->getOutdegree()<<" places and "<<vertex->getIndegree()<<" go to it"<<endl;
    }
    cout << "****************************************\n" << "*               TEST-3 v               *\n"
         << "****************************************\n";
    set<Airport> airports;
    set<string>  countries;
    set<string> cities;

    vector<int> ans=system.getNumberOfDestinations("JFK",airports,countries,cities);
    cout<<"IT GOES TO"<<ans[0]<<" airports"<<endl;
    cout<<"IT GOES TO"<<ans[1]<<" countries"<<endl;
    cout<<"IT GOES TO"<<ans[2]<<" cities"<<endl;


    return 0;
}
