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

    /**
     * @brief Gets the total number of airports.
     * @return Integer representing the total numbers of airports.
     */
    int GlobalNumberOfAirports();

    /**
     * @brief Returns global number of available flights.
     * @return Integer representing the total number of flights.
     */
    int GlobalNumberOfFlights();

    /**
     * @brief Returns global number of articulations points.
     * @return Integer representing the total number of articulation points.
     */
    int articulationPoints();

    /**
     * @brief
     * @param v Current vertex.
     * @param s Auxiliary stack of vertices.
     * @param l Set of vertices that are articulation points.
     * @param i Auxiliary counter.
     */
    void dfs_art(Vertex<Airport> *v, stack<Airport> &s, set<Airport> &l, int &i);

    /**
     * @brief Gets the numbers of destinations possible from a given airport.
     * @param airportString The code of the airport.
     * @param airports Auxiliary set of airports containing the possible destinations.
     * @param countries Auxiliary set of countries containing the possible destinations.
     * @param cities Auxiliary set of cities containing the possible destinations.
     * @return Vector with 3 elements: the number of airports, countries and cities.
     */
    vector<int>
    getNumberOfDestinations(string airportString, set<Airport> &airports, set<string> &countries, set<string> &cities);

    /**
     * @brief Prints details of a given airport, like number of flights, countries and airlines.
     * @param airportString The airport code.
     */
    void airportDetails(string airportString);

    /**
     * @brief Prints details of a given country, like number of flights, countries and airlines.
     * @param countryName The name of the country.
     */
    void countryDetails(string countryName);

    /**
     * @brief Prints details of a given city, like number of flights, countries and airlines.
     * @param cityName The name of the city.
     */
    void cityDetails(string cityName);

    /**
     * @brief Prints details of a given airline, like number of flights and airports.
     * @param airlineCode The code of the airline.
     */
    void airlineDetails(string airlineCode);

    /**
    * @brief Get the top k airports with the maximum number of flights.
    * @param k The number of top airports to retrieve.
    * @return A vector of pairs, where each pair contains an airport and the corresponding number of flights.
    */
    vector<pair<Airport, int>> topkAirportsMaxFlights(int k);

};

#endif //AED_FLIGHTS_MANAGEMENTSYSTEM_H
