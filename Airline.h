//
// Created by jose on 19-12-2023.
//

#ifndef AED_FLIGHTS_AIRLINE_H
#define AED_FLIGHTS_AIRLINE_H


#include <string>

class Airline {
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;

public:
    Airline(const std::string& code, const std::string& name, const std::string& callsign, const std::string& country)
            : code(code), name(name), callsign(callsign), country(country) {}

    // Getter methods
    std::string getCode() const { return code; }
    std::string getName() const { return name; }
    std::string getCallsign() const { return callsign; }
    std::string getCountry() const { return country; }
};

#endif //AED_FLIGHTS_AIRLINE_H
