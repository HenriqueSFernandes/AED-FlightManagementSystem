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
    explicit Menu(const ManagementSystem &system);

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
};


#endif //AED_FLIGHTS_MENU_H
