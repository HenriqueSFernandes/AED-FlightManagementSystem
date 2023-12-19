#ifndef AED_FLIGHTS_AIRLINE_H
#define AED_FLIGHTS_AIRLINE_H


#include <string>

class Airline {
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;
public:
    const std::string &getCode() const {
        return code;
    }

    void setCode(const std::string &code) {
        Airline::code = code;
    }

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        Airline::name = name;
    }

    const std::string &getCallsign() const {
        return callsign;
    }

    void setCallsign(const std::string &callsign) {
        Airline::callsign = callsign;
    }

    const std::string &getCountry() const {
        return country;
    }

    void setCountry(const std::string &country) {
        Airline::country = country;
    }

public:
    Airline(const std::string &code, const std::string &name, const std::string &callsign, const std::string &country)
            : code(code), name(name), callsign(callsign), country(country) {}


    bool operator<(const Airline &other) const {
        return code < other.code;
    }

    bool operator==(const Airline &rhs) const {
        return code == rhs.code;
    }

    bool operator!=(const Airline &rhs) const {
        return !(rhs == *this);
    }

    struct HashFunction {
        size_t operator()(const Airline &airline) const {
            return std::hash<std::string>()(airline.getCode());
        }
    };

};

#endif //AED_FLIGHTS_AIRLINE_H
