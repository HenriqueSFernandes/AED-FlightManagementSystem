/// @file ManagementSystem.h
#ifndef AED_FLIGHTS_MANAGEMENTSYSTEM_H
#define AED_FLIGHTS_MANAGEMENTSYSTEM_H

#include "Airport.h"
#include <unordered_set>
#include <map>
#include "Airline.h"
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
     *
     * Complexity is, on average, O(n), where n is the number of airlines.
     */
    void readAirlines();

    /**
     * @brief Read airports from the csv file.
     *
     * Complexity is O(n log(k)), where n is the number of airports and k is the number of cities.
     */
    void readAirports();

    /**
     * @brief Read flights from the csv file.
     *
     * Complexity is, on average, O(n * k) where n is the number of flights and k is the number of airlines per flight.
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
     *
     * Complexity is O(n * k) where n is the number of airports and k is the number of flights per airport.
     */
    int GlobalNumberOfFlights();

    /**
     * @brief Returns the essential airports.
     *
     * Complexity is O(n * k + n + n³ + kn²) where n is the number of airports and k is the number of flights per airport.
     * @return Set representing the essential points.
     */
    set<Airport> essentialAirports();

    /**
     * @brief Auxiliary DFS function for finding articulation points.
     *
     * Complexity is O(n * (n + k) where n is the number of airports and k is the number of flights per airport.
     * @param v Current vertex.
     * @param s Auxiliary stack of vertices.
     * @param l Set of vertices that are articulation points.
     * @param i Auxiliary counter.
     */
    void dfs_art(Vertex<Airport> *v, stack<Airport> &s, set<Airport> &l, int &i);

    /**
     * @brief Gets the numbers of destinations possible from a given airport.
     *
     * Complexity is O(n + k + nlog(n)) where n is the number of airports and k is the number of flights per airport.
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
     *
     * Complexity is O(n + k + nlog(n)) where n is the number of airports and k is the number of flights per airport.
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
     *
     * Complexity is O(n * k) where n is the number of flights and k is the number of airlines per flight.
     * @param airportString The airport code.
     */
    void airportDetails(string airportString);

    /**
     * @brief Prints details of a given country, like number of flights, countries and airlines.
     *
     * Complexity is O(n * k * l) where n is the number of airports, k is the number of flights per airport and l is the number of airlines per flight.
     * @param countryName The name of the country.
     */
    void countryDetails(string countryName);

    /**
     * @brief Prints details of a given city, like number of flights, countries and airlines.
     *
     * Complexity is O(n * k * l) where n is the number of airports, k is the number of flights per airport and l is the number of airlines per flight.
     * @param cityName The name of the city.
     */
    void cityDetails(string cityName);

    /**
     * @brief Prints details of a given airline, like number of flights and airports.
     *
     * Complexity is  O(n * k) where n is the number of airports and k is the number of flights per airport.
     * @param airlineCode The code of the airline.
     */
    void airlineDetails(string airlineCode);

    /**
    * @brief Get the top k airports with the maximum number of flights.
     *
     * Complexity is  O(n * k + log(n)) where n is the number of airports and k is the number of flights per airport.
    * @param k The number of top airports to retrieve.
    * @return A vector of pairs, where each pair contains an airport and the corresponding number of flights.
    */
    vector<pair<Airport, int>> topKAirportsMaxFlights(int k);

    /**
     * @brief Perform BFS traversal to find the maximum distance and set of airports in the diameter.
     *
     * Complexity is O(n + k) where n is the number of airports and k is the number of flights.
     * @param v The starting vertex for BFS traversal.
     * @return A pair containing the maximum distance and the set of airports at that distance.
     */
    pair<int, set<Airport>> bfsDistanceWithDest(Vertex<Airport> *v);

    /**
     * @brief Find the maximum diameter and corresponding set of airport pairs in the graph.
     *
     * Complexity is O(n² + kn) where n is the number of airports and k is the number of flights.
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
     * @brief Auxiliary function that determines if all airlines are part of the filtered airlines.
     *
     * Complexity is O(n * log(k)) where n is the number of airlines and k is the number of filtered airlines.
     * @param airlines Set with the current airlines.
     * @param filteredAirlines Set with the filtered airlines.
     * @return True if all airlines are part of the filtered airlines.
     */
    bool containsFilteredAirline(set<Airline> airlines, set<Airline> filteredAirlines);

    /**
     * @brief Finds the best flight options for a trip.
     *
     * Complexity is O(n² + kn) where n is the number of airports and k is the number of flights.
     * @param sourceAirports A set with the source airports.
     * @param targetAirports A set with the target airports.
     * @param filteredAirports A set with the filtered airports (airports that should not be considered while searching).
     * @param filteredAirlines A set with the filtered airlines (airlines that should not be considered while searching).
     * @return The best trip (a trip is a vector of airports).
     */


    vector<vector<Airport>> findBestFlights(set<Airport> sourceAirports, set<Airport> targetAirports);
    /**
     * @brief Prints given airports in the specified image file
     * @param airports
     * @param destinationFile
     */
    void printAirports(set<Airport> airports, string destinationFile);
    /**
     * @brief Helper prints direct path between A and B
     * @param airport1
     * @param airport2
     * @param destinationFile
     */
    void printPath(Airport airport1, Airport airport2, string destinationFile);
    /**
     * @brief Prints path
     * @param mySet
     * @param destinationFile
     */
    void printComposedPath(vector<Airport> mySet, string destinationFile);
      /**
     * @brief Finds the best flight options for a trip.
     *
     * Complexity is O(n² + kn) where n is the number of airports and k is the number of flights.
     * @param sourceAirports A set with the source airports.
     * @param targetAirports A set with the target airports.
     * @param filteredAirports A set with the filtered airports (airports that should not be considered while searching).
     * @param filteredAirlines A set with the filtered airlines (airlines that should not be considered while searching).
     * @return The best trip (a trip is a vector of pairs airport-airlines).
     */

    vector<pair<Airport, set<Airline>>> findBestFlight(vector<Vertex<Airport> *> sourceAirports, vector<Vertex<Airport> *> targetAirports, vector<Vertex<Airport> *> filteredAirports, set<Airline> filteredAirlines);


    /**
     * @brief Makes the graph undirected by duplicating edges.
     *
     * Complexity is O(n * k) where n is the number of airports and k is the number of flights per airport.
     */
    void MakeUndirected();
};

#endif //AED_FLIGHTS_MANAGEMENTSYSTEM_H
