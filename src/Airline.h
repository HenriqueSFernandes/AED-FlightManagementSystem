#ifndef AED_FLIGHTS_AIRLINE_H
#define AED_FLIGHTS_AIRLINE_H


#include <string>
#include <utility>

class Airline {
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;
public:
    [[nodiscard]] const std::string &getCode() const;

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] const std::string &getCallsign() const;

    [[nodiscard]] const std::string &getCountry() const;

    Airline(std::string code, std::string name, std::string callsign, std::string country);

    bool operator<(const Airline &other) const;

    bool operator==(const Airline &rhs) const;

    bool operator!=(const Airline &rhs) const;

    struct HashFunction {
        size_t operator()(const Airline &airline) const;
    };

};

#endif //AED_FLIGHTS_AIRLINE_H
