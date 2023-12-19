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
    unordered_set<Airport, Airport::HashFunction> airports;
    set<Flight> flights;
public:
    const Graph<Airport> &getAirportNetwork() const;

    const unordered_set<Airline, Airline::HashFunction> &getAirlines() const;

    const unordered_set<Airport, Airport::HashFunction> &getAirportsMap() const;

    const set<Flight> &getFlights() const;

    void readAirlines();

    void readAirports();

    void readFlights();
};

#endif //AED_FLIGHTS_MANAGEMENTSYSTEM_H
