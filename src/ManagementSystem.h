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
    /**
     * @brief Airport network graph getter.
     * @return The graph representing the airport network.
     */
    const Graph<Airport> &getAirportNetwork() const;

    /**
     * @brief Airlines getter.
     * @return An unordered set of all the airlines.
     */
    const unordered_set<Airline, Airline::HashFunction> &getAirlines() const;

    /**
     * @brief Airports getter.
     * @return An unordered set of all the airports.
     */
    const unordered_set<Airport, Airport::HashFunction> &getAirports() const;

    /**
     * @brief Flights getter.
     * @return A set of all the flights.
     */
    const set<Flight> &getFlights() const;

    /**
     * @brief Read airlines from the csv file.
     */
    void readAirlines();

    /**
     * @brief Read airports from the csv file.
     */
    void readAirports();

    /**
     * @brief Read flights from the csv file.
     */
    void readFlights();

    vector<int>
    getNumberOfDestinations(Airport airport, set<Airport> &airports, set<string> &countries, set<string> &cities);

    vector<int>
    getNumberOfDestinations(string airportString, set<Airport> &airports, set<string> &countries, set<string> &cities);
};

#endif //AED_FLIGHTS_MANAGEMENTSYSTEM_H
