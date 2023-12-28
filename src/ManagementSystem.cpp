
#include "ManagementSystem.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>

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
        airports.insert(newAirport);
        airportNetwork.addVertex(newAirport);

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
        // Get the airline and airports for the flight
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
            set<Airline> airlines = {*airline};
            airportNetwork.addEdge(sourceAirportVertex->getInfo(), targetAirportVertex->getInfo(), airlines);
            sourceAirportVertex->setOutdegree(sourceAirportVertex->getOutdegree() + 1);
            targetAirportVertex->setIndegree(targetAirportVertex->getIndegree() + 1);
        }

    }
    flightsFile.close();
}

int ManagementSystem::GlobalNumberOfAirports() {
    return airportNetwork.getNumVertex();
}

int ManagementSystem::GlobalNumberOfFlights() {
    int numberOfFlights = 0;
    for (auto vertex: airportNetwork.getVertexSet()) {
        for (auto edge: vertex->getAdj()) {
            numberOfFlights += edge.getAirlines().size();
        }
    }
    return numberOfFlights;
}

set<Airport> ManagementSystem::essentialAirports() {
    set<Airport> res;
    int k = 1;
    for (auto vertex: airportNetwork.getVertexSet()) {
        vertex->setVisited(false);
        vertex->setProcessing(false);
        vertex->setIndegree(0);
    }
    for (auto vertex: airportNetwork.getVertexSet()) {
        if (!vertex->isVisited()) {
            k = 1;
            stack<Airport> s;
            ManagementSystem::dfs_art(vertex, s, res, k);
        }
    }
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
        if (treeedges > 1 and v->getNum() == 1) {
            // cout<<"here"<<v->getInfo().getCode()<<endl;
            //l.insert(v->getInfo());
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


const unordered_set<Airport, Airport::HashFunction> &ManagementSystem::getAirports() const {
    return airports;
}

const set<Flight> &ManagementSystem::getFlights() const {
    return flights;
}

void ManagementSystem::airportDetails(string airportString) {
    // Finds the airport
    auto sourceAirportVertex = airportNetwork.findVertex(Airport(airportString, "", "", "", 0, 0));
    if (sourceAirportVertex == nullptr) {
        cout << "The airport doesn't exist!\n";
        return;
    }
    set<string> availableCountries;
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
    vector <pair<Airline, int>> sortedEntries(availableAirlines.begin(), availableAirlines.end());
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
    set<string> countriesAvailable;
    int flightCount = 0;
    bool countryFound = false;
    // Iterate over every airport
    for (Vertex<Airport> *vertexAirport: getAirportNetwork().getVertexSet()) {
        if (vertexAirport->getInfo().getCountry() == countryName) {
            countryFound = true;
            countryAirports[vertexAirport->getInfo()] = 0;

            for (Edge<Airport> flight: vertexAirport->getAdj()) {
                countryAirports[vertexAirport->getInfo()]++;
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
    string countryName;
    map<Airport, int> cityAirports;
    map<Airline, int> cityAirlines;
    set<string> countriesAvailable;
    int flightCount = 0;
    bool cityFound = false;
    for (Vertex<Airport> *vertexAirport: getAirportNetwork().getVertexSet()) {
        if (vertexAirport->getInfo().getCity() == cityName) {
            cityFound = true;
            countryName = vertexAirport->getInfo().getCountry();
            cityAirports[vertexAirport->getInfo()] = 0;
            for (Edge<Airport> flight: vertexAirport->getAdj()) {
                flightCount++;
                cityAirports[vertexAirport->getInfo()]++;
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
    if (!cityFound) {
        cout << "The city doesn't exist!\n";
        return;
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
        cout << "\t\t" << airport.first.getName() << " (" << airport.first.getCode() << ") with " << airport.second << " outgoing flights\n";
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
    set<string> availableCountries;
    auto airline = airlines.find(Airline(airlineCode, "", "", ""));
    if (airline == nullptr) {
        cout << "The airline doesn't exist!\n";
        return;
    }
    cout << "Details for " << airline->getName() << " (" << airline->getCallsign() << ") , located in "
         << airline->getCountry() << ":\n";
    for (Vertex<Airport> *airportVertex: getAirportNetwork().getVertexSet()) {
        for (Edge<Airport> flight: airportVertex->getAdj()) {
            if (flight.getAirlines().find(Airline(airlineCode, "", "", "")) != flight.getAirlines().end()) {
                flightCount++;
                availableCountries.insert(flight.getDest()->getInfo().getCountry());
                if (availableAirports.find(airportVertex->getInfo()) == availableAirports.end()) {
                    availableAirports[airportVertex->getInfo()] = 1;
                } else {
                    availableAirports[airportVertex->getInfo()]++;
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
    for (auto vertex: airportNetwork.getVertexSet()) {
        count = 0;
        for (Edge<Airport> edge: vertex->getAdj()) {
            count += edge.getAirlines().size();
        }
        pairs.insert({count, vertex->getInfo()});
    }
    for (auto it = pairs.rbegin(); it != pairs.rend() && k > 0; ++it, --k) {
        res.push_back({it->second, it->first});
    }
    return res;
}




pair<int, set<Airport>> ManagementSystem::bfsDistanceWithDest(Vertex<Airport> *v) {
    // Reset all vertices to distance 0 and mark them as not visited
    for (auto vertex: airportNetwork.getVertexSet()) {
        vertex->setVisited(false);
        vertex->setDistance(0);
    }

    // Queue for BFS traversal
    queue<Vertex<Airport> *> q;
    q.push(v);
    v->setVisited(true);
    v->setDistance(0);
    int max = 0;
    set<Airport> dest;

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
    for (auto vertex: airportNetwork.getVertexSet()) {
        // Perform BFS to find the maximum diameter and set of airports at that distance
        pair<int, set<Airport>> res = bfsDistanceWithDest(vertex);
        int val = res.first;
        set<Airport> dest = res.second;

        // If the current diameter equals the max diameter, add airport pairs to the result set
        if (val == max) {
            for (auto i: dest) {
                resAirports.insert({vertex->getInfo(), i});
            }
        }

        // If the current diameter is greater than the max diameter, update max and clear the result set
        if (max < val) {
            max = val;
            resAirports.clear();
            for (auto i: dest) {
                resAirports.insert({vertex->getInfo(), i});
            }
        }
    }

    // Return the result as a pair of set of airport pairs and the maximum diameter
    return {resAirports, max};
}
