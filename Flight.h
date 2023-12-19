//
// Created by jose on 19-12-2023.
//

#ifndef AED_FLIGHTS_FLIGHT_H
#define AED_FLIGHTS_FLIGHT_H

#include <string>
#include <set>
#include <stdio.h>
#include <iostream>
#include "Airline.h"

class Flight {
    std::string source;
    std::string target;
    std::set<Airline> airlines;

public:
    Flight(const std::string& source, const std::string& target) : source(source), target(target) {}

    // Function to add an airline to the set for this flight
    void addAirline(const Airline& airline) {
        airlines.insert(airline);
    }

    // Function to display information about the flight and its airlines
    void displayFlightInfo() const {
        std::cout << "Flight from " << source << " to " << target << " with the following airlines:\n";
        for (const auto& airline : airlines) {
            std::cout << "  Code: " << airline.getCode()
                      << ", Name: " << airline.getName()
                      << ", Callsign: " << airline.getCallsign()
                      << ", Country: " << airline.getCountry() << "\n";
        }
        std::cout << std::endl;
    }
};

#endif //AED_FLIGHTS_FLIGHT_H
