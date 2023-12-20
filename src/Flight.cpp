#include "Flight.h"

void Flight::addAirline(Airline airline) {
    airlines.insert(airline);
}

bool Flight::operator<(const Flight &rhs) const {
    if ((source < rhs.source) || (source == rhs.source && target < rhs.target))
        return true;
    return false;
}

const std::string &Flight::getSource() const {
    return source;
}

const std::string &Flight::getTarget() const {
    return target;
}

const std::set<Airline> &Flight::getAirlines() const {
    return airlines;
}

Flight::Flight(std::string source, std::string target) : source(std::move(source)), target(std::move(target)) {}

std::ostream &operator<<(std::ostream &os, const Flight &flight) {
    os << "Source: " << flight.getSource() << ", Target: " << flight.getTarget() << ", Airlines:";
    for (const Airline &airline: flight.getAirlines()) {
        os << "\n\t- " << airline;
    }
    return os;
}
