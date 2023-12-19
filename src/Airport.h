#ifndef AED_FLIGHTS_AIRPORT_H
#define AED_FLIGHTS_AIRPORT_H

#include <string>

class Airport {
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    double latitude;
    double longitude;

public:
    Airport(std::string code, std::string name, std::string city, std::string country, double latitude, double longitude)
        : code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude) {}

    // Getter methods
    std::string getCode() const { return code; }
    std::string getCity() const { return city; }
    std::string getCountry() const { return country; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

    // Setter methods
    void setCode(const std::string& newCode) { code = newCode; }
    void setCity(const std::string& newCity) { city = newCity; }
    void setCountry(const std::string& newCountry) { country = newCountry; }
    void setLatitude(double newLatitude) { latitude = newLatitude; }
    void setLongitude(double newLongitude) { longitude = newLongitude; }

    // Comparison operator
    bool operator<(const Airport& other) const {
        return code < other.code;
    }

    bool operator==(const Airport& rhs) const {
        return code == rhs.code &&
               name == rhs.name &&
               city == rhs.city &&
               country == rhs.country &&
               latitude == rhs.latitude &&
               longitude == rhs.longitude;
    }

    bool operator!=(const Airport& rhs) const {
        return !(rhs == *this);
    }

    struct HashFunction {
        size_t operator()(const Airport& airport) const {
            return std::hash<std::string>()(airport.getCode());
        }
    };
};

#endif //AED_FLIGHTS_AIRPORT_H
