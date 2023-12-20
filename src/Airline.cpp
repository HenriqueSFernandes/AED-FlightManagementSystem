#include "Airline.h"

const std::string &Airline::getCode() const {
    return code;
}

const std::string &Airline::getName() const {
    return name;
}

const std::string &Airline::getCallsign() const {
    return callsign;
}

const std::string &Airline::getCountry() const {
    return country;
}

bool Airline::operator<(const Airline &other) const {
    return code < other.code;
}

bool Airline::operator==(const Airline &rhs) const {
    return code == rhs.code;
}

bool Airline::operator!=(const Airline &rhs) const {
    return !(rhs == *this);
}

Airline::Airline(std::string code, std::string name, std::string callsign, std::string country)
        : code(std::move(code)), name(std::move(name)), callsign(std::move(callsign)),
          country(std::move(country)) {}

std::ostream &operator<<(std::ostream &os, const Airline &airline) {
    os << "Code: " << airline.getCode() << ", Name: " << airline.getName() << ", Abbreviation: "
       << airline.getCallsign() << ", Country: " << airline.getCountry();
    return os;
}

size_t Airline::HashFunction::operator()(const Airline &airline) const {
    return std::hash<std::string>()(airline.getCode());
}


