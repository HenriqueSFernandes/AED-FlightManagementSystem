/// @file ManagementSystem.h
#ifndef AED_FLIGHTS_MANAGEMENTSYSTEM_H
#define AED_FLIGHTS_MANAGEMENTSYSTEM_H

#include "Airport.h"
#include <unordered_set>
#include <map>
#include "Airline.h"
#include "Flight.h"
#include "Graph.h"

/**
 * @brief Class used to handle the core functions of the program, like loading the data files and building the network.
 */
class ManagementSystem {
private:
    Graph<Airport> airportNetwork;
    unordered_set<Airline, Airline::HashFunction> airlines;
    map<string, vector<string>> cities;
public:
    const map<string, vector<string>> &getCities() const;

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
     * @brief Returns the essential airports..
     * @return Set representing the essential points.
     */
    set<Airport> essentialAirports();

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
     *
     * @brief Gets the numbers of destinations possible from a given airport in X layovers.
     * @param airportString The code of the airport.
     * @param airports Auxiliary set of airports.
     * @param countries Auxiliary set of countries.
     * @param cities Auxiliary set of cities.
     * @param x The maximum number of layovers.
     * @return Vector with 3 elements: the number of airports, countries and cities.
     */
    vector<int> getNumberOfDestinationsInXLayovers(string airportString, set<Airport> &airports, set<string> &countries,
                                                   set<string> &cities, int x);

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
    vector<pair<Airport, int>> topKAirportsMaxFlights(int k);

    /**
     * @brief Perform BFS traversal to find the maximum distance and set of airports in the diameter.
     * @param v The starting vertex for BFS traversal.
     * @return A pair containing the maximum distance and the set of airports at that distance.
     */
    pair<int, set<Airport>> bfsDistanceWithDest(Vertex<Airport> *v);

    /**
     * @brief Find the maximum diameter and corresponding set of airport pairs in the graph.
     * @return A pair containing the set of airport pairs in the maximum diameter and the diameter value.
     */
    pair<set<pair<Airport, Airport>>, int> maxTripWithSourceDest();

    /**
     * @brief This functions calculates the spherical distance between 2 airports.
     * @param airport1 The code of the first airport.
     * @param airport2 The code of the second airport.
     * @return The spherical distance between the 2 airports.
     */
    double airportDistance(string airport1, string airport2);

    /**
     * @brief This function uses the haversine distance to calculate distance between 2 points on a sphere.
     * @param lat1 First point latitude.
     * @param lon1 First point longitude.
     * @param lat2 Second point latitude.
     * @param lon2 Second point longitude.
     * @return The distance between the points.
     */
    double haversine(double lat1, double lon1, double lat2, double lon2);

    /**
     * @brief Finds the best flight options for a trip.
     * @param sourceAirports A set with the source airports.
     * @param targetAirports A set with the target airports.
     * @param filteredAirports A set with the filtered airports (airports that should not be considered while searching).
     * @param filteredAirlines A set with the filtered airlines (airlines that should not be considered while searching).
     * @return A vector of trips (a trip is a vector of airports). This vector is ordered from shortest trip to longest.
     */
    vector<vector<Airport>> findBestFlights(set<Vertex<Airport> *> sourceAirports, set<Vertex<Airport> *> targetAirports, set<Vertex<Airport> *> filteredAirports, set<Airline> filteredAirlines);

};

#endif //AED_FLIGHTS_MANAGEMENTSYSTEM_H
