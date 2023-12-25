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
    cout << "****************************************\n" << "*              QUESTION 3-I TEST             *\n"
         << "****************************************\n";
    cout<<"GLOBAL NUMBER OF AIRPORTS IS"<<system.GlobalNumberOfAirports()<<endl;
    cout<<"GLOCBAL NUMBER OF AVAILABLE FLIGHTS IS"<<system.GlobalNumberOfFlights()<<endl;
    cout << "****************************************\n" << "*              QUESTION 3-IX TEST             *\n"
        << "****************************************\n";
    cout<<system.articulationPoints()<<endl;
    return 0;
}
