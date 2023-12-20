#ifndef AED_FLIGHTS_AIRPORT_H
#define AED_FLIGHTS_AIRPORT_H

#include <string>
#include <iostream>

class Airport {
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    double latitude;
    double longitude;

public:
    Airport(std::string code, std::string name, std::string city, std::string country, double latitude,
            double longitude);

    [[nodiscard]] std::string getCode() const;

    [[nodiscard]] std::string getCity() const;

    [[nodiscard]] std::string getCountry() const;

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] double getLatitude() const;

    [[nodiscard]] double getLongitude() const;

    bool operator<(const Airport &other) const;

    bool operator==(const Airport &rhs) const;

    bool operator!=(const Airport &rhs) const;

    struct HashFunction {
        size_t operator()(const Airport &airport) const;
    };

    friend std::ostream &operator<<(std::ostream &os, const Airport &airport);
};

#endif //AED_FLIGHTS_AIRPORT_H