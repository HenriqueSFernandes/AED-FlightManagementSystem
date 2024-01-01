
#include "ManagementSystem.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <cmath>
#include "Image/Script.hpp"

using namespace std;

void ManagementSystem::readAirlines() {
    string code;
    string name;
    string callsign;
    string country;
    ifstream airlinesFile("../data/airlines.csv");

    if (!airlinesFile) {
        cerr << "Failed to open file\n";
        return;
    }

    string line;
    getline(airlinesFile, line); // Ignore header

    // Iterate over every line of the file, split the line, create a new class and append that class to the list of classes.
    while (getline(airlinesFile, line)) {
        istringstream iss(line);
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callsign, ',');
        getline(iss, country, '\r');
        Airline airline(code, name, callsign, country);
        airlines.insert(airline);
    }

    airlinesFile.close();
}

void ManagementSystem::readAirports() {
    ifstream airportsFile("../data/airports.csv");
    if (!airportsFile) {
        cerr << "Failed to open file\n";
        return;
    }
    string line;
    getline(airportsFile, line); // Ignore header
    string code;
    string name;
    string city;
    string country;
    string latitude;
    string longitude;
    // Iterate over every line of the file, split the line, create a new lesson and add that lesson to the respective class.
    while (getline(airportsFile, line)) {
        istringstream iss(line);
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, country, ',');
        getline(iss, latitude, ',');
        getline(iss, longitude, '\r');
        Airport newAirport = Airport(code, name, city, country, stod(latitude), stod(longitude));
        airportNetwork.addVertex(newAirport);
        // Search for cities with the same name.
        auto mappedCity = cities.find(city);
        if (mappedCity == cities.end()) {
            vector<string> countries = {country};
            cities[city] = countries;
        } else {
            if (std::find(mappedCity->second.begin(), mappedCity->second.end(), country) == mappedCity->second.end()) {
                mappedCity->second.push_back(country);
            }
        }
    }
    airportsFile.close();

}

void ManagementSystem::readFlights() {
    ifstream flightsFile("../data/flights.csv");
    if (!flightsFile) {
        cerr << "Failed to open file\n";
        return;
    }
    string line;
    string source;
    string target;
    string airlineCode;


    getline(flightsFile, line); // Ignore header
    while (getline(flightsFile, line)) {
        istringstream iss(line);
        getline(iss, source, ',');
        getline(iss, target, ',');
        getline(iss, airlineCode, '\r');
        // Get the airline and airports for the flight.
        auto airline = airlines.find(Airline(airlineCode, "", "", ""));
        auto sourceAirportVertex = airportNetwork.findVertex(Airport(source, "", "", "", 0, 0));
        auto targetAirportVertex = airportNetwork.findVertex(Airport(target, "", "", "", 0, 0));
        bool flightExists = false;
        for (const Edge<Airport> &flight: sourceAirportVertex->getAdj()) {
            Edge<Airport> *flightPtr = const_cast<Edge<Airport> *>(&flight);
            if (flight.getDest()->getInfo().getCode() == targetAirportVertex->getInfo().getCode()) {
                flightExists = true;
                flightPtr->addAirline(*airline);
            }
        }
        if (!flightExists) {
            set < Airline > airlines = {*airline};
            double distance = airportDistance(sourceAirportVertex->getInfo().getCode(),
                                              targetAirportVertex->getInfo().getCode());
            airportNetwork.addEdge(sourceAirportVertex->getInfo(), targetAirportVertex->getInfo(), airlines, distance);
            sourceAirportVertex->setOutdegree(sourceAirportVertex->getOutdegree() + 1);
            targetAirportVertex->setIndegree(targetAirportVertex->getIndegree() + 1);
        }
    }
    flightsFile.close();
}

void ManagementSystem::printAirports(set<Airport> airports, string destinationFile) {
    prog::Script script = prog::Script();
    script.open("src/Image/input/worldmap.png");
    for (auto airport: airports) {
        int x = round(airport.getLongitude() * 1.7621 + 343.4);
        int y = 260 - round(1.23 * (450 / (2 * M_PI) * log2(tan(M_PI / 4 + airport.getLatitude() * M_PI * 0.4 / 180))));
        if (airport.getLatitude() < 0) {
            y = round(airport.getLatitude() * (-1.909) + 258.71);
        } else {
            if (airport.getLatitude() > 60) {
                y = round(airport.getLatitude() * (-2.209) + 268.71);
            } else {
                y = round(-1.909 * airport.getLatitude() + 261.71);
            }

        }


        script.fill(x, y, 3, 3, 255, 0, 0);

    }
    script.save(destinationFile);
}

void ManagementSystem::printPath(Airport airport1, Airport airport2, string destinationFile) {
    prog::Script script = prog::Script();
    script.open(destinationFile);
    double currentLat;
    double targetLat;
    if (min(airport1.getLongitude(), airport2.getLongitude()) == airport1.getLongitude()) {
        currentLat = airport1.getLatitude();
        targetLat = airport2.getLatitude();
    } else {
        currentLat = airport2.getLatitude();
        targetLat = airport1.getLatitude();
    }
    double currentLong = min(airport1.getLongitude(), airport2.getLongitude());
    double targetLong = max(airport1.getLongitude(), airport2.getLongitude());
    while (abs(targetLat - currentLat) > 0.01 or abs(targetLong - currentLong) > 0.01) {
        if (currentLong < -180) {
            currentLong = 180;
        }
        if (currentLong > 180) {
            currentLong = -180;
        }
        double deltaX = (targetLong - currentLong) / 360;
        if (targetLong - currentLong > 180) {
            deltaX = (180 - targetLong + currentLong) / 360;
        }
        currentLong += deltaX;
        double deltay = (targetLat - currentLat) / 180;
        currentLat += deltay;
        int x = round(currentLong * 1.7621 + 343.4);
        int y = 260 - round(1.23 * (450 / (2 * M_PI) * log2(tan(M_PI / 4 + currentLat * M_PI * 0.4 / 180))));
        script.fill(x, y, 2, 2, 255, 0, 0);
    }


    script.save(destinationFile);


}

void ManagementSystem::printComposedPath(vector<Airport> mySet, string destinationFile) {
    prog::Script script = prog::Script();
    script.open("src/Image/input/worldmap.png");
    script.save(destinationFile);

    if (mySet.empty()) {
        return;  // Nothing to print if the set is empty
    }

    auto it = mySet.begin();
    while (it != std::prev(mySet.end())) {
        auto currentAirport = *it;
        auto nextIt = std::next(it);

        if (nextIt == mySet.end()) {
            break;
        }

        auto nextAirport = *nextIt;

        printPath(currentAirport, nextAirport, destinationFile);

        ++it;
    }
}

double ManagementSystem::haversine(double lat1, double lon1,
                                   double lat2, double lon2) {
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

double ManagementSystem::airportDistance(string airport1, string airport2) {
    auto sourceAirportVertex = airportNetwork.findVertex(Airport(airport1, "", "", "", 0, 0));
    auto destinationAirportVertex = airportNetwork.findVertex(Airport(airport2, "", "", "", 0, 0));
    if (sourceAirportVertex != nullptr and destinationAirportVertex != nullptr) {
        return haversine(sourceAirportVertex->getInfo().getLatitude(), sourceAirportVertex->getInfo().getLongitude(),
                         destinationAirportVertex->getInfo().getLatitude(),
                         destinationAirportVertex->getInfo().getLongitude());
    } else {
        cout << "Invalid airports\n";
        return 0;
    }

}

int ManagementSystem::GlobalNumberOfAirports() {
    return airportNetwork.getNumVertex();
}

int ManagementSystem::GlobalNumberOfFlights() {
    int numberOfFlights = 0;
    for (pair<string, Vertex<Airport> *> vertex: airportNetwork.getVertexSet()) {
        for (Edge<Airport> edge: vertex.second->getAdj()) {
            numberOfFlights += edge.getAirlines().size();
        }
    }
    return numberOfFlights;
}

void ManagementSystem::MakeUndirected() {
    for (auto vertex: airportNetwork.getVertexSet()) {
        for (auto edge: vertex.second->getAdj()) {
            airportNetwork.addEdge(edge.getDest()->getInfo(), vertex.second->getInfo(), {}, 0);
        }
    }

}

set<Airport> ManagementSystem::essentialAirports() {
    set < Airport > res;
    int k = 1;
    Graph<Airport> recover = airportNetwork;
    MakeUndirected();

    for (pair<string, Vertex<Airport> *> vertex: airportNetwork.getVertexSet()) {
        vertex.second->setVisited(false);
        vertex.second->setProcessing(false);
        vertex.second->setIndegree(0);
    }
    for (pair<string, Vertex<Airport> *> vertex: airportNetwork.getVertexSet()) {
        if (!vertex.second->isVisited()) {
            k = 1;
            stack<Airport> s;
            ManagementSystem::dfs_art(vertex.second, s, res, k);
        }
    }
    airportNetwork = recover;
    return res;
}

void ManagementSystem::dfs_art(Vertex<Airport> *v, stack<Airport> &s, set<Airport> &l, int &i) {

    v->setLow(i);
    v->setNum(i);
    v->setProcessing(true);
    v->setVisited(true);
    s.push(v->getInfo());
    i++;
    int treeedges = 0;
    for (auto &edge: v->getAdj()) {
        if (!edge.getDest()->isVisited()) {
            treeedges++;
            dfs_art(edge.getDest(), s, l, i);
            v->setLow(min(v->getLow(), edge.getDest()->getLow()));
            if (edge.getDest()->getLow() >= v->getNum()) {
                if (v->getNum() != 1) {
                    l.insert(v->getInfo());
                }
            }
        } else if (edge.getDest()->isProcessing()) {
            v->setLow(min(v->getLow(), edge.getDest()->getNum()));
        }
    }
    v->setProcessing(false);
    s.pop();
}

vector<int>
ManagementSystem::getNumberOfDestinations(string airportString, set<Airport> &airports, set<string> &countries,
                                          set<string> &cities) {
    auto sourceAirportVertex = airportNetwork.findVertex(Airport(airportString, "", "", "", 0, 0));
    if (sourceAirportVertex == nullptr) {
        cout << "The airport doesn't exist!\n";
        vector<int> res = {};
        return res;
    }
    vector<Airport> visitableAirports = airportNetwork.dfs(sourceAirportVertex->getInfo());
    int numAirports = 0;
    int numCountries = 0;
    int numCities = 0;
    for (Vertex<Airport> airportVertex: visitableAirports) {
        Airport airport = airportVertex.getInfo();
        if (airports.find(airport) == airports.end()) {
            airports.insert(airport);
            numAirports++;
        }
        if (countries.find(airport.getCountry()) == countries.end()) {
            countries.insert(airport.getCountry());
            numCountries++;
        }
        if (cities.find(airport.getCity()) == cities.end()) {
            cities.insert(airport.getCity());
            numCities++;
        }
    }
    vector<int> ans;
    ans.push_back(numAirports);
    ans.push_back(numCountries);
    ans.push_back(numCities);
    return ans;

}

vector<int>
ManagementSystem::getNumberOfDestinationsInXLayovers(string airportString, set<Airport> &airports,
                                                     set<string> &countries,
                                                     set<string> &cities, int x) {
    auto sourceAirportVertex = airportNetwork.findVertex(Airport(airportString, "", "", "", 0, 0));
    if (sourceAirportVertex == nullptr) {
        cout << "The airport doesn't exist!\n";
        vector<int> res = {};
        return res;
    }
    // Gets all the airports at distance x.
    vector<Airport> visitableAirports = airportNetwork.bfsLimited(sourceAirportVertex->getInfo(), x + 1);
    int numAirports = 0;
    int numCountries = 0;
    int numCities = 0;
    // Iterates over the visitable airports and updates the counters.
    for (Vertex<Airport> airportVertex: visitableAirports) {
        Airport airport = airportVertex.getInfo();
        if (airports.find(airport) == airports.end()) {
            airports.insert(airport);
            numAirports++;
        }
        if (countries.find(airport.getCountry()) == countries.end()) {
            countries.insert(airport.getCountry());
            numCountries++;
        }
        if (cities.find(airport.getCity()) == cities.end()) {
            cities.insert(airport.getCity());
            numCities++;
        }
    }
    vector<int> ans;
    ans.push_back(numAirports);
    ans.push_back(numCountries);
    ans.push_back(numCities);
    return ans;
}


const Graph<Airport> &ManagementSystem::getAirportNetwork() const {
    return airportNetwork;
}


const unordered_set<Airline, Airline::HashFunction> &ManagementSystem::getAirlines() const {
    return airlines;
}

void ManagementSystem::airportDetails(string airportString) {
    // Finds the airport
    auto sourceAirportVertex = airportNetwork.findVertex(Airport(airportString, "", "", "", 0, 0));
    if (sourceAirportVertex == nullptr) {
        cout << "The airport doesn't exist!\n";
        return;
    }
    set < string > availableCountries;
    map<Airline, int> availableAirlines;
    // Iterates over every flight and gets the different countries and airlines.
    for (Edge<Airport> flight: sourceAirportVertex->getAdj()) {
        availableCountries.insert(flight.getDest()->getInfo().getCountry());
        for (Airline airline: flight.getAirlines()) {
            if (availableAirlines.find(airline) == availableAirlines.end()) {
                availableAirlines[airline] = 1;
            } else {
                availableAirlines[airline]++;
            }
        }
    }
    // Sorts the airlines by the number of flights.
    vector<pair<Airline, int>> sortedEntries(availableAirlines.begin(), availableAirlines.end());
    std::sort(sortedEntries.begin(), sortedEntries.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    cout << "Details for " << sourceAirportVertex->getInfo().getName() << " ("
         << sourceAirportVertex->getInfo().getCode() << "):\n";
    cout << "\tThis airport is based in " << sourceAirportVertex->getInfo().getCity() << ", "
         << sourceAirportVertex->getInfo().getCountry() << endl;
    cout << "\tThere are " << sourceAirportVertex->getAdj().size() << " available destinations to "
         << availableCountries.size() << " different countries, ";
    cout << "which means this airport covers " << fixed << setprecision(2) << availableCountries.size() / 225.0 * 100
         << "% of all the countries.\n";
    cout << "\tThese flights are made by a total of " << availableAirlines.size()
         << " airlines, which are the following:\n";
    for (pair<Airline, int> airline: sortedEntries) {
        cout << "\t\t" << airline.first.getName() << " (" << airline.first.getCode() << ") with " << airline.second
             << " outgoing flight(s).\n";
    }
}

void ManagementSystem::countryDetails(string countryName) {
    map<Airport, int> countryAirports;
    map<Airline, int> countryAirlines;
    set < string > countriesAvailable;
    int flightCount = 0;
    bool countryFound = false;
    // Iterate over every airport
    for (pair<string, Vertex<Airport> *> vertexAirport: getAirportNetwork().getVertexSet()) {
        if (vertexAirport.second->getInfo().getCountry() == countryName) {
            countryFound = true;
            countryAirports[vertexAirport.second->getInfo()] = 0;

            for (Edge<Airport> flight: vertexAirport.second->getAdj()) {
                countryAirports[vertexAirport.second->getInfo()]++;
                flightCount++;
                for (Airline airline: flight.getAirlines()) {
                    if (countryAirlines.find(airline) == countryAirlines.end()) {
                        countryAirlines[airline] = 1;
                    } else {
                        countryAirlines[airline]++;
                    }
                }
                countriesAvailable.insert(flight.getDest()->getInfo().getCountry());
            }
        }
    }
    if (!countryFound) {
        cout << "The country doesn't exist!\n";
        return;
    }

    vector<pair<Airline, int>> sortedAirlines(countryAirlines.begin(), countryAirlines.end());
    std::sort(sortedAirlines.begin(), sortedAirlines.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    vector<pair<Airport, int>> sortedAirports(countryAirports.begin(), countryAirports.end());
    std::sort(sortedAirports.begin(), sortedAirports.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    cout << "Details for " << countryName << ":\n";
    cout << "\tThere are " << countryAirports.size() << " airports in " << countryName << ":\n";
    for (pair<Airport, int> airport: sortedAirports) {
        cout << "\t\t" << airport.first.getName() << " (" << airport.first.getCode() << ") located in "
             << airport.first.getCity() << " with " << airport.second << " outgoing flights\n";
    }
    cout << "\tThere are " << flightCount << " available destinations to " << countriesAvailable.size()
         << " different countries, which means this country covers " << fixed << setprecision(2)
         << countriesAvailable.size() / 225.0 * 100
         << "% of all the countries.\n";
    cout << "\tThese flights are made by a total of " << countryAirlines.size()
         << " airlines, which are the following:\n";
    for (pair<Airline, int> airline: sortedAirlines) {
        cout << "\t\t" << airline.first.getName() << " (" << airline.first.getCode() << ") with " << airline.second
             << " outgoing flight(s).\n";
    }
}

void ManagementSystem::cityDetails(string cityName) {
    auto mappedCity = cities.find(cityName);
    if (mappedCity == cities.end()) {
        cout << "The city doesn't exist!\n";
        return;
    }
    string countryName;
    if (mappedCity->second.size() > 1) {
        cout << "There are more than one city with that name, can you specify the country?\n";
        for (int i = 1; i <= mappedCity->second.size(); i++) {
            cout << "\t" << i << ") " << mappedCity->second[i - 1] << endl;
        }
        int option;
        cin >> option;
        countryName = mappedCity->second[option - 1];
    } else {
        countryName = mappedCity->second[0];
    }

    map<Airport, int> cityAirports;
    map<Airline, int> cityAirlines;
    set < string > countriesAvailable;
    int flightCount = 0;
    for (pair<string, Vertex<Airport> *> vertexAirport: getAirportNetwork().getVertexSet()) {
        if (vertexAirport.second->getInfo().getCity() == cityName &&
            vertexAirport.second->getInfo().getCountry() == countryName) {
            countryName = vertexAirport.second->getInfo().getCountry();
            cityAirports[vertexAirport.second->getInfo()] = 0;
            for (Edge<Airport> flight: vertexAirport.second->getAdj()) {
                flightCount++;
                cityAirports[vertexAirport.second->getInfo()]++;
                for (Airline airline: flight.getAirlines()) {
                    if (cityAirlines.find(airline) == cityAirlines.end()) {
                        cityAirlines[airline] = 1;
                    } else {
                        cityAirlines[airline]++;
                    }
                }
                countriesAvailable.insert(flight.getDest()->getInfo().getCountry());
            }
        }
    }

    vector<pair<Airline, int>> sortedAirlines(cityAirlines.begin(), cityAirlines.end());
    std::sort(sortedAirlines.begin(), sortedAirlines.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    vector<pair<Airport, int>> sortedAirports(cityAirports.begin(), cityAirports.end());
    std::sort(sortedAirports.begin(), sortedAirports.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    cout << "Details for " << cityName << ", located in " << countryName << ":\n";
    cout << "\tThere are " << cityAirports.size() << " airports in " << cityName << ":\n";
    for (pair<Airport, int> airport: sortedAirports) {
        cout << "\t\t" << airport.first.getName() << " (" << airport.first.getCode() << ") with " << airport.second
             << " outgoing flights\n";
    }
    cout << "\tThere are " << flightCount << " available destinations to " << countriesAvailable.size()
         << " different countries, which means this country covers " << fixed << setprecision(2)
         << countriesAvailable.size() / 225.0 * 100
         << "% of all the countries.\n";
    cout << "\tThese flights are made by a total of " << cityAirlines.size()
         << " airlines, which are the following:\n";
    for (pair<Airline, int> airline: sortedAirlines) {
        cout << "\t\t" << airline.first.getName() << " (" << airline.first.getCode() << ") with " << airline.second
             << " outgoing flight(s).\n";
    }

}

void ManagementSystem::airlineDetails(string airlineCode) {
    map<Airport, int> availableAirports;
    int flightCount = 0;
    set < string > availableCountries;
    auto airline = airlines.find(Airline(airlineCode, "", "", ""));
    if (airline == airlines.end()) {
        cout << "The airline doesn't exist!\n";
        return;
    }
    cout << "Details for " << airline->getName() << " (" << airline->getCallsign() << ") , located in "
         << airline->getCountry() << ":\n";
    for (pair<string, Vertex<Airport> *> airportVertex: getAirportNetwork().getVertexSet()) {
        for (Edge<Airport> flight: airportVertex.second->getAdj()) {
            if (flight.getAirlines().find(Airline(airlineCode, "", "", "")) != flight.getAirlines().end()) {
                flightCount++;
                availableCountries.insert(flight.getDest()->getInfo().getCountry());
                if (availableAirports.find(airportVertex.second->getInfo()) == availableAirports.end()) {
                    availableAirports[airportVertex.second->getInfo()] = 1;
                } else {
                    availableAirports[airportVertex.second->getInfo()]++;
                }
            }
        }
    }

    cout << "\tThis airline is responsible for " << flightCount << " flights to " << availableCountries.size()
         << " different countries, which means this airline covers " << fixed << setprecision(2)
         << availableCountries.size() / 225.0 * 100
         << "% of all the countries.\n";
    cout << "\tThis airline operates in " << availableAirports.size() << " different airports.\n";
}


vector<pair<Airport, int>> ManagementSystem::topKAirportsMaxFlights(int k) {
    set<pair<int, Airport>> pairs;
    vector<pair<Airport, int>> res;
    int count;
    for (pair<string, Vertex<Airport> *> vertex: airportNetwork.getVertexSet()) {
        count = 0;
        for (Edge<Airport> edge: vertex.second->getAdj()) {
            count += edge.getAirlines().size();
        }
        pairs.insert({count, vertex.second->getInfo()});
    }
    for (auto it = pairs.rbegin(); it != pairs.rend() && k > 0; ++it, --k) {
        res.push_back({it->second, it->first});
    }
    return res;
}


pair<int, set<Airport>> ManagementSystem::bfsDistanceWithDest(Vertex<Airport> *v) {
    // Reset all vertices to distance 0 and mark them as not visited
    for (pair<string, Vertex<Airport> *> vertex: airportNetwork.getVertexSet()) {
        vertex.second->setVisited(false);
        vertex.second->setDistance(0);
    }

    // Queue for BFS traversal
    queue<Vertex<Airport> *> q;
    q.push(v);
    v->setVisited(true);
    v->setDistance(0);
    int max = 0;
    set < Airport > dest;

    // BFS traversal
    while (!q.empty()) {
        auto sourceVertex = q.front();
        q.pop();

        for (const auto &e: sourceVertex->getAdj()) {
            auto destVertex = e.getDest();
            if (!destVertex->isVisited()) {
                q.push(destVertex);
                destVertex->setVisited(true);
                destVertex->setDistance(sourceVertex->getDistance() + 1);

                // If the distance is equal to the current max, add the airport to the set
                if (destVertex->getDistance() == max) {
                    dest.insert(destVertex->getInfo());
                }

                // If the distance is greater than the current max, update max and clear the set
                if (destVertex->getDistance() > max) {
                    max = destVertex->getDistance();
                    dest.clear();
                    dest.insert(destVertex->getInfo());
                }
            }
        }
    }

    // Return the result as a pair of max distance and set of airports
    return {max, dest};
}


pair<set<pair<Airport, Airport>>, int> ManagementSystem::maxTripWithSourceDest() {
    // Initialize the maximum diameter to -1 and the set of airport pairs
    int max = -1;
    set<pair<Airport, Airport>> resAirports;

    // Iterate through all vertices in the airport network
    for (pair<string, Vertex<Airport> *> vertex: airportNetwork.getVertexSet()) {
        // Perform BFS to find the maximum diameter and set of airports at that distance
        pair<int, set<Airport>> res = bfsDistanceWithDest(vertex.second);
        int val = res.first;
        set < Airport > dest = res.second;

        // If the current diameter equals the max diameter, add airport pairs to the result set
        if (val == max) {
            for (auto i: dest) {
                resAirports.insert({vertex.second->getInfo(), i});
            }
        }

        // If the current diameter is greater than the max diameter, update max and clear the result set
        if (max < val) {
            max = val;
            resAirports.clear();
            for (auto i: dest) {
                resAirports.insert({vertex.second->getInfo(), i});
            }
        }
    }

    // Return the result as a pair of set of airport pairs and the maximum diameter
    return {resAirports, max};
}

bool ManagementSystem::containsFilteredAirline(set<Airline> airlines, set<Airline> filteredAirlines) {
    for (Airline airline: airlines) {
        if (filteredAirlines.find(airline) == filteredAirlines.end()) {
            return false;
        }
    }
    return true;
}

vector<pair<Airport, set<Airline>>>
ManagementSystem::findBestFlight(const vector<Vertex<Airport> *> &sourceAirports,
                                 const vector<Vertex<Airport> *> &targetAirports,
                                 const vector<Vertex<Airport> *> &filteredAirports,
                                 const set<Airline> &filteredAirlines) {
    vector<vector<pair<Airport, set<Airline>>>> res;
    set < Airport > foundtargets;
    for (Vertex<Airport> *sourceAirportVertex: sourceAirports) {
        Airport sourceAirport = sourceAirportVertex->getInfo();
        // Auxiliary queue to help in BFS. The first element of the pair is the current airport, the second is the path to that airport (the path is a vector of pairs Airport-Airlines)..
        queue<pair<Vertex<Airport> *, vector<pair<Airport, set<Airline>>>>> auxQueue;
        // Set all airports to not visited.
        for (pair<string, Vertex<Airport> *> airport: airportNetwork.getVertexSet()) {
            airport.second->setVisited(false);
        }
        // Set the filtered airports as visited, so they won't be considered when searching.
        for (Vertex<Airport> *airportVertex: filteredAirports) {
            airportVertex->setVisited(true);
        }
        // Set the vertex as visited.
        sourceAirportVertex->setVisited(true);
        // Add the source vertex to the queue.

        auxQueue.push({sourceAirportVertex, {{sourceAirport, {}}}});
        // Integer that saves the distance between the source and the target.
        int foundDistance = -1;
        // Perform BFS.
        while (!auxQueue.empty()) {
            Vertex<Airport> *currentAirportVertex = auxQueue.front().first;
            // If the current airport is a target airport update the found distance and stop adding new airports to the queue.
            if (std::find(targetAirports.begin(), targetAirports.end(), currentAirportVertex) != targetAirports.end()) {
                foundtargets.insert(currentAirportVertex->getInfo());
                foundDistance = auxQueue.front().second.size();
                res.push_back(auxQueue.front().second);

            }
            if (foundDistance == -1) {
                // Get the adjacent flights and add them to que queue.
                for (Edge<Airport> flight: currentAirportVertex->getAdj()) {
                    // If the destination has not been visited and there is at least one valid airline then add it to the queue.
                    if (!(flight.getDest()->isVisited()) &&
                        !containsFilteredAirline(flight.getAirlines(), filteredAirlines)) {

                        flight.getDest()->setVisited(true);
                        vector<pair<Airport, set<Airline>>> path = auxQueue.front().second;
                        set < Airline > airlines;
                        for (Airline airline: flight.getAirlines()) {
                            if (filteredAirlines.find(airline) == filteredAirlines.end()) {
                                airlines.insert(airline);
                            }
                        }
                        path.push_back({flight.getDest()->getInfo(), airlines});
                        auxQueue.push({flight.getDest(), path});
                    }
                }
            }
            auxQueue.pop();
        }
    }
    // Sort the result by number of stops.
    std::sort(res.begin(), res.end(), [](const auto &a, const auto &b) {
        return a.size() < b.size();
    });
    if (res.empty()) {
        return {};
    }
    return res[0];
}

const map<string, vector<string>> &ManagementSystem::getCities() const {
    return cities;
}
