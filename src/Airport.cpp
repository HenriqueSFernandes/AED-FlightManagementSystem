#include "Airport.h"

#include <utility>

Airport::Airport(std::string code, std::string name, std::string city, std::string country, double latitude,
                 double longitude)
        : code(std::move(code)), name(std::move(name)), city(std::move(city)), country(std::move(country)),
          latitude(latitude), longitude(longitude) {}

std::string Airport::getCode() const { return code; }

std::string Airport::getCity() const { return city; }

std::string Airport::getCountry() const { return country; }

double Airport::getLatitude() const { return latitude; }

double Airport::getLongitude() const { return longitude; }

bool Airport::operator<(const Airport &other) const {
    return code < other.code;
}

bool Airport::operator==(const Airport &rhs) const {
    return code == rhs.code;
}

bool Airport::operator!=(const Airport &rhs) const {
    return this->code != rhs.code;
}

std::string Airport::getName() const { return name; }

std::ostream &operator<<(std::ostream &os, const Airport &airport) {
    os << "Code: " << airport.getCode() << ", Name: " << airport.getName() << ", City: " << airport.getCity()
       << ", Country: " << airport.getCountry() << ", Coordinates: " << airport.getLatitude() << " "
       << airport.getLongitude();
    return os;
}

size_t Airport::HashFunction::operator()(const Airport &airport) const {
    return std::hash<std::string>()(airport.getCode());
}
