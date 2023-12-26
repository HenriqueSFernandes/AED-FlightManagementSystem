
#include "ManagementSystem.h"
#include <fstream>
#include <sstream>

using namespace std;

void ManagementSystem::readAirlines() {
    string code;
    string name;
    string callsign;
    string country;
    ifstream airlinesFile("../data/airlines.csv");

    if (!airlinesFile) {
        cerr << "Failed to open file\n";
        return;
    }

    string line;
    getline(airlinesFile, line); // Ignore header

    // Iterate over every line of the file, split the line, create a new class and append that class to the list of classes.
    while (getline(airlinesFile, line)) {
        istringstream iss(line);
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callsign, ',');
        getline(iss, country, '\r');
        Airline airline(code, name, callsign, country);
        airlines.insert(airline);
    }

    airlinesFile.close();
}

void ManagementSystem::readAirports() {
    ifstream airportsFile("../data/airports.csv");
    if (!airportsFile) {
        cerr << "Failed to open file\n";
        return;
    }
    string line;
    getline(airportsFile, line); // Ignore header
    string code;
    string name;
    string city;
    string country;
    string latitude;
    string longitude;
    // Iterate over every line of the file, split the line, create a new lesson and add that lesson to the respective class.
    while (getline(airportsFile, line)) {
        istringstream iss(line);
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, country, ',');
        getline(iss, latitude, ',');
        getline(iss, longitude, '\r');
        Airport newAirport = Airport(code, name, city, country, stod(latitude), stod(longitude));
        airports.insert(newAirport);
        airportNetwork.addVertex(newAirport);

    }
    airportsFile.close();

}

void ManagementSystem::readFlights() {
    ifstream flightsFile("../data/flights.csv");
    if (!flightsFile) {
        cerr << "Failed to open file\n";
        return;
    }
    string line;
    string source;
    string target;
    string airlineCode;


    getline(flightsFile, line); // Ignore header
    while (getline(flightsFile, line)) {
        istringstream iss(line);
        getline(iss, source, ',');
        getline(iss, target, ',');
        getline(iss, airlineCode, '\r');
        // Get the airline and airports for the flight
        auto airline = airlines.find(Airline(airlineCode, "", "", ""));
        auto sourceAirportVertex = airportNetwork.findVertex(Airport(source, "", "", "", 0, 0));
        auto targetAirportVertex = airportNetwork.findVertex(Airport(target, "", "", "", 0, 0));
        bool flightExists = false;
        for (Edge<Airport> flight: sourceAirportVertex->getAdj()) {
            if (flight.getDest() == targetAirportVertex) {
                flightExists = true;
                flight.addAirline(*airline);
            }
        }
        if (!flightExists) {
            set<Airline> airlines = {*airline};
            airportNetwork.addEdge(sourceAirportVertex->getInfo(), targetAirportVertex->getInfo(), airlines);
            sourceAirportVertex->setOutdegree(sourceAirportVertex->getOutdegree() + 1);
            targetAirportVertex->setIndegree(targetAirportVertex->getIndegree() + 1);
        }

    }
    flightsFile.close();
}

vector<int>
ManagementSystem::getNumberOfDestinations(string airportString, set<Airport> &airports, set<string> &countries,
                                          set<string> &cities) {
    auto sourceAirportVertex = airportNetwork.findVertex(Airport(airportString, "", "", "", 0, 0));
    vector<Airport> visitableAirports = airportNetwork.dfs(sourceAirportVertex->getInfo());
    int numAirports = 0;
    int numCountries = 0;
    int numCities = 0;
    for (Vertex<Airport> airportVertex: visitableAirports) {
        Airport airport = airportVertex.getInfo();
        if (airports.find(airport) == airports.end()) {
            airports.insert(airport);
            numAirports++;
        }
        if (countries.find(airport.getCountry()) == countries.end()) {
            countries.insert(airport.getCountry());
            numCountries++;
        }
        if (cities.find(airport.getCity()) == cities.end()) {
            cities.insert(airport.getCity());
            numCities++;
        }
    }
    vector<int> ans;
    ans.push_back(numAirports);
    ans.push_back(numCountries);
    ans.push_back(numCities);
    return ans;

}

const Graph<Airport> &ManagementSystem::getAirportNetwork() const {
    return airportNetwork;
}


const unordered_set<Airline, Airline::HashFunction> &ManagementSystem::getAirlines() const {
    return airlines;
}


const unordered_set<Airport, Airport::HashFunction> &ManagementSystem::getAirports() const {
    return airports;
}

const set<Flight> &ManagementSystem::getFlights() const {
    return flights;
}
