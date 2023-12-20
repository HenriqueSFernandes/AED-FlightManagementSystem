#ifndef AED_FLIGHTS_FLIGHT_H
#define AED_FLIGHTS_FLIGHT_H

#include <string>
#include <set>
#include <iostream>
#include <utility>
#include "Airline.h"

class Flight {
private:
    std::string source;
    std::string target;
    std::set<Airline> airlines;
public:
    [[nodiscard]] const std::string &getSource() const;

    [[nodiscard]] const std::string &getTarget() const;

    [[nodiscard]] const std::set<Airline> &getAirlines() const;

    Flight(std::string source, std::string target);

    void addAirline(Airline airline);

    bool operator<(const Flight &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Flight &flight);
};

#endif //AED_FLIGHTS_FLIGHT_H
