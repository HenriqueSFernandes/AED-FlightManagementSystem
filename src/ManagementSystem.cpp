
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

int ManagementSystem::articulationPoints() {
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
    for (auto el: res) {
        cout << el.getCode() << endl;
    }
    return res.size();
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
    // Gets all the airports at distance x.
    vector<Airport> visitableAirports = airportNetwork.bfsLimited(sourceAirportVertex->getInfo(), x);
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
