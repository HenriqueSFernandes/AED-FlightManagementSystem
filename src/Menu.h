/// @file Menu.h
#ifndef AED_FLIGHTS_MENU_H
#define AED_FLIGHTS_MENU_H


#include "ManagementSystem.h"

/**
 * @brief Class used to represent a user friendly menu.
 */
class Menu {
private:
    ManagementSystem system;
public:
    /**
     * @brief Parameterized constructor.
     * @param system Management system.
     */
    explicit Menu(ManagementSystem system);

    /**
     * @brief Main menu.
     */
    void start();

    /**
     * @brief Statistics menu.
     */
    void statisticsMenu();

    /**
     * @brief Menu with statistics about airports.
     */
    void airportStatisticsMenu();

    /**
     * @brief Menu with statistics about flights.
     */
    void flightStatisticsMenu();

    /**
     * @brief Menu searching flights.
     */
    void flightSearchMenu();

    /**
     * @brief Menu for adding airport(s) to the current selection.
     * @param airports A vector of the currently selected airports.
     */
    void addAirportMenu(vector<Vertex<Airport> *> &airports);

    /**
     * @brief Menu for removing airport(s) to the current selection
     * @param airports A vector of the currently selected airports.
     */
    void removeAirportMenu(vector<Vertex<Airport> *> &airports);

    /**
     * @brief Menu for changing the filters.
     * @param filteredAirports A set with the filtered airports (airports that should not be considered while searching).
     * @param filteredAirlines A set with the filtered airlines (airlines that should not be considered while searching).
     * @param mandatoryStops A set with airports that need to be visited (layover).
     * @param mandatoryAirlines A set with the only airlines than can be used.
     */
    void filterMenu(vector<Vertex<Airport> *> &filteredAirports, set<Airline> &filteredAirlines,
                    vector<Vertex<Airport> *> &mandatoryStops, set<Airline> &mandatoryAirlines);

    static void printTrip(const vector<pair<Airport, set<Airline>>>& trip) ;
};


#endif //AED_FLIGHTS_MENU_H
