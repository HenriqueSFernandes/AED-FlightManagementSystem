#ifndef AED_FLIGHTS_AIRPORT_H
#define AED_FLIGHTS_AIRPORT_H

#include <string>

class Airport {
    int code;
    std::string city;
    std::string country;
    double latitude;
    double longitude;

public:
    Airport(int code, std::string city, std::string country, double latitude, double longitude)
            : code(code), city(city), country(country), latitude(latitude), longitude(longitude) {}

    // Getter methods
    int getCode() const { return code; }
    std::string getCity() const { return city; }
    std::string getCountry() const { return country; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

    // Setter methods
    void setCode(int newCode) { code = newCode; }
    void setCity(const std::string& newCity) { city = newCity; }
    void setCountry(const std::string& newCountry) { country = newCountry; }
    void setLatitude(double newLatitude) { latitude = newLatitude; }
    void setLongitude(double newLongitude) { longitude = newLongitude; }
};

#endif //AED_FLIGHTS_AIRPORT_H
