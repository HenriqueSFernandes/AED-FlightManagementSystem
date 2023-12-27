#ifndef AED_FLIGHTS_MENU_H
#define AED_FLIGHTS_MENU_H


#include "ManagementSystem.h"

class Menu {
private:
    ManagementSystem system;
public:
    explicit Menu(const ManagementSystem &system);
    void start();
    void statisticsMenu();
};


#endif //AED_FLIGHTS_MENU_H