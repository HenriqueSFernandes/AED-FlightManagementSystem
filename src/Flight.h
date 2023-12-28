/// @file Flight.h
#ifndef AED_FLIGHTS_FLIGHT_H
#define AED_FLIGHTS_FLIGHT_H

#include <string>
#include <set>
#include <iostream>
#include <utility>
#include "Airline.h"

/**
 * @brief Class used to represent a flight.
 */
class Flight {
private:
    std::string source;
    std::string target;
    std::set<Airline> airlines;
public:
    /**
     * @brief Flight source airport getter.
     * @return A string representing the source airport code.
     */
    [[nodiscard]] const std::string &getSource() const;

    /**
     * @brief Flight target airport getter.
     * @return A string representing the target airport code.
     */
    [[nodiscard]] const std::string &getTarget() const;

    /**
     * @brief Flight airlines getter.
     * @return A set of all the airlines carrying out the flight.
     */
    [[nodiscard]] const std::set<Airline> &getAirlines() const;

    /**
     * @brief Flight parameterized constructor.
     * @param source String representing the source airport code.
     * @param target String representing the target airport code.
     */
    Flight(std::string source, std::string target);

    /**
     * @brief Add a airline to the flight
     * @param airline Airline to be added.
     */
    void addAirline(Airline airline);

    /**
     * @brief Flight _less than_ operator overload.
     * @param rhs The flight to compare to.
     * @return True if the current flight source and target airports code are smaller than the other flight airports.
     */
    bool operator<(const Flight &rhs) const;

    /**
     * @brief Flight _output stream_ operator overload.
     * @param os Output stream.
     * @param flight Flight to output.
     * @return Output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Flight &flight);
};

#endif //AED_FLIGHTS_FLIGHT_H
