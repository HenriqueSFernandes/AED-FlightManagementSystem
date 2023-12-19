#ifndef AED_FLIGHTS_MANAGEMENTSYSTEM_H
#define AED_FLIGHTS_MANAGEMENTSYSTEM_H

#include "Airport.h"
#include <unordered_set>
#include "Airline.h"
#include "Flight.h"
#include "Graph.h"

class ManagementSystem {
private:
    Graph<Airport> airportNetwork;
    unordered_set<Airline, Airline::HashFunction> airlines;
public:
    const Graph<Airport> &getAirportNetwork() const;

    void setAirportNetwork(const Graph<Airport> &airportNetwork);

    const unordered_set<Airline, Airline::HashFunction> &getAirlines() const;

    void setAirlines(const unordered_set<Airline, Airline::HashFunction> &airlines);

    const unordered_set<Airport, Airport::HashFunction> &getAirportsMap() const;

    void setAirportsMap(const unordered_set<Airport, Airport::HashFunction> &airportsMap);

    const set<Flight> &getFlights() const;

    void setFlights(const set<Flight> &flights);

private:
    unordered_set<Airport, Airport::HashFunction> AirportsMap;
    set<Flight> flights;


public:

    // TODO placeholder
    void readAirlines();

    void readAirports();

    void readFlights();

};

#endif //AED_FLIGHTS_MANAGEMENTSYSTEM_H
