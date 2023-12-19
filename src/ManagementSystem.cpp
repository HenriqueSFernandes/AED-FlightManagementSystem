
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
        airlines.insert(airline);    }

    airlinesFile.close();
}

void ManagementSystem::readAirports() {
    ifstream Airports("../data/airports.csv");
    if (!Airports) {
        cerr << "Failed to open file\n";
        return;
    }
    string line;
    getline(Airports, line); // Ignore header
    string Code;
    string Name;
    string City;
    string Country;
    string Latitude;
    string Longitude;
    // Iterate over every line of the file, split the line, create a new lesson and add that lesson to the respective class.
    while (getline(Airports, line)) {
        istringstream iss(line);
        getline(iss, Code, ',');
        getline(iss, Name, ',');
        getline(iss, City, ',');
        getline(iss, Country, ',');
        getline(iss, Latitude, ',');
        getline(iss, Longitude, '\r');
        const Airport newAirport = Airport(Code, Name, City, Country, stod(Latitude), stod(Longitude));
        AirportsMap.insert(newAirport);
        airportNetwork.addVertex(newAirport);

    }
    Airports.close();

}

void ManagementSystem::readFlights() {
    ifstream Flights("../data/flights.csv");
    if (!Flights) {
        cerr << "Failed to open file\n";
        return;
    }
    string line;
    string Source;
    string Target;
    string CodeAirline;


    getline(Flights, line); // Ignore header
    while (getline(Flights, line)) {
        istringstream iss(line);
        getline(iss, Source, ',');
        getline(iss, Target, ',');
        getline(iss, CodeAirline, '\r');
        auto airline = airlines.find(Airline(CodeAirline, "", "", ""));
        set<Flight>::iterator flight = flights.find(Flight(Source, Target));
        if (flight == flights.end()) {
            Flight newFlight(Source, Target);
            newFlight.addAirline(*airline);
            flights.insert(newFlight);
        } else {
            Flight newFlight = *flight;
            flights.erase(flight);
            newFlight.addAirline(*airline);
            flights.insert(newFlight);
        }
    }
    Flights.close();
}

const Graph<Airport> &ManagementSystem::getAirportNetwork() const {
    return airportNetwork;
}

void ManagementSystem::setAirportNetwork(const Graph<Airport> &airportNetwork) {
    ManagementSystem::airportNetwork = airportNetwork;
}

const unordered_set<Airline, Airline::HashFunction> &ManagementSystem::getAirlines() const {
    return airlines;
}

void ManagementSystem::setAirlines(const unordered_set<Airline, Airline::HashFunction> &airlines) {
    ManagementSystem::airlines = airlines;
}

const unordered_set<Airport, Airport::HashFunction> &ManagementSystem::getAirportsMap() const {
    return AirportsMap;
}

void ManagementSystem::setAirportsMap(const unordered_set<Airport, Airport::HashFunction> &airportsMap) {
    AirportsMap = airportsMap;
}

const set<Flight> &ManagementSystem::getFlights() const {
    return flights;
}

void ManagementSystem::setFlights(const set<Flight> &flights) {
    ManagementSystem::flights = flights;
}
