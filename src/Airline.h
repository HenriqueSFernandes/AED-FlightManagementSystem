#ifndef AED_FLIGHTS_AIRLINE_H
#define AED_FLIGHTS_AIRLINE_H


#include <string>
#include <utility>
#include <iostream>

class Airline {
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;
public:
    /**
     * @brief Airline code getter.
     * @return A string representing the airline code.
     */
    [[nodiscard]] const std::string &getCode() const;

    /**
     * @brief Airline name getter.
     * @return A string representing the airline name.
     */
    [[nodiscard]] const std::string &getName() const;

    /**
     * @brief Airline callsign getter.
     * @return A string representing the airline callsign.
     */
    [[nodiscard]] const std::string &getCallsign() const;

    /**
     * @brief Airline origin country getter.
     * @return A string representing the country.
     */
    [[nodiscard]] const std::string &getCountry() const;

    /**
     * @brief Airline parameterized constructor.
     * @param code String representing the airline code.
     * @param name String representing the airline name.
     * @param callsign String representing the airline callsign.
     * @param country String representing the airline origin country.
     */
    Airline(std::string code, std::string name, std::string callsign, std::string country);

    /**
     * @brief Airline _less than_ operator overload.
     * @param other The airline to compare to.
     * @return True if the current airline code is less than the other airline code.
     */
    bool operator<(const Airline &other) const;

    /**
     * @brief Airline _equal_ operator overload.
     * @param rhs The airline to compare to.
     * @return True if the current airline code is equal to the other airline code.
     */
    bool operator==(const Airline &rhs) const;

    /**
     * @brief Airline _different_ operator overload.
     * @param rhs The airline to compare to.
     * @return True if the current airline code is different than the other airline code.
     */
    bool operator!=(const Airline &rhs) const;

    struct HashFunction {
        /**
         * @brief Hash function to store airlines.
         * @param airline The airline to hash.
         */
        size_t operator()(const Airline &airline) const;
    };

    /**
     * @brief Airline _output stream_ operator overload.
     * @param os Output stream.
     * @param airline Airline to output.
     * @return Output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Airline &airline);

};

#endif //AED_FLIGHTS_AIRLINE_H
