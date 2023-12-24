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
    /**
     * @brief Airport parameterized constructor.
     * @param code String representing the airport code.
     * @param name String representing the airport name.
     * @param city String representing the airport city.
     * @param country String representing the airport country.
     * @param latitude Double representing the airport coordinates latitude.
     * @param longitude Double representing the airport coordinates longitude.
     */
    Airport(std::string code, std::string name, std::string city, std::string country, double latitude,
            double longitude);

    /**
     * @brief Airport code getter.
     * @return A string representing the airport code.
     */
    [[nodiscard]] std::string getCode() const;

    /**
     * @brief Airport name getter,
     * @return A string representing the airport name.
     */
    [[nodiscard]] std::string getName() const;

    /**
     * @brief Airport city getter.
     * @return A string representing the airport city.
     */
    [[nodiscard]] std::string getCity() const;

    /**
     * @brief Airport country getter.
     * @return A string representing the airport country.
     */
    [[nodiscard]] std::string getCountry() const;

    /**
     * @brief Airport latitude getter.
     * @return A double representing the airport coordinates latitude.
     */
    [[nodiscard]] double getLatitude() const;

    /**
     * @brief Airport longitude getter.
     * @return A double representing the airport coordinates longitude.
     */
    [[nodiscard]] double getLongitude() const;

    /**
     * @brief Airport _less than_ operator overload.
     * @param other The airport to compare to
     * @return True if the current airport code is less than the other airport code.
     */
    bool operator<(const Airport &other) const;

    /**
     * @brief Airport _equal_ operator overload.
     * @param rhs The airport to compare to.
     * @return True if the current airport code is equal to the other airport code.
     */
    bool operator==(const Airport &rhs) const;

    /**
     * @brief Airport _different_ operator overload.
     * @param rhs The airport to compare to.
     * @return True if the current airport code is different than the other airport code.
     */
    bool operator!=(const Airport &rhs) const;

    struct HashFunction {
        /**
         * @brief Hash function to store hash airports.
         * @param airline The airport to hash.
         */
        size_t operator()(const Airport &airport) const;
    };

    /**
     * @brief Airport _output stream_ operator overload.
     * @param os Output stream.
     * @param airline Airport to output.
     * @return Output stream.
     */

    friend std::ostream &operator<<(std::ostream &os, const Airport &airport);
};

#endif //AED_FLIGHTS_AIRPORT_H
