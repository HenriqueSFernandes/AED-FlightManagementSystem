#include "Menu.h"

Menu::Menu(const ManagementSystem &system) : system(system) {}

void Menu::start() {
    string option;
    cout << "Hello, welcome to the flight database!\n";
    while (true) {
        cout << "\nWhat do you want to do?\n";
        cout << "1) Get statistics about the flight network\n2) Search for a flight\n3) Exit\n";
        cin >> option;
        if (option == "1") {
            statisticsMenu();
        } else if (option == "2") {
            cout << "searching for flights...\n";
        } else if (option == "3") {
            exit(0);
        } else {
            cout << "Invalid option, please choose again.\n";
        }
    }
}

void Menu::statisticsMenu() {
    string option;
    cout << "There are a total of " << system.GlobalNumberOfFlights() << " in " << system.GlobalNumberOfAirports()
         << " airports.\n";
    while (true) {
        cout << "\nWhat do you want statistics on?\n";
        cout << "1) Airports\n2) Airlines\n3) Flights\n4) Cities\n5) Countries\n6) Go back\n";
        cin >> option;

        if (option == "1") {
            airportStatisticsMenu();
        } else if (option == "2") {
            string airlineCode;
            cout << "Please enter the code of the airline\n";
            cin >> airlineCode;
            system.airlineDetails(airlineCode);
        } else if (option == "3") {
            flightStatisticsMenu();
        } else if (option == "4") {
            string cityName;
            cout << "Please enter the name of the city\n";
            cin >> cityName;
            system.cityDetails(cityName);
        } else if (option == "5") {
            string countryName;
            cout << "Please enter the name of the country\n";
            cin >> countryName;
            system.countryDetails(countryName);
        } else if (option == "6") {
            break;
        } else {
            cout << "Invalid option, please choose again.\n";
        }
    }
}

void Menu::airportStatisticsMenu() {
    string option;
    while (true) {
        cout << "\nWhat do you want to do?.\n";
        cout
                << "1) Full airport details\n2) Top airports with the most flights\n3) Available destinations\n4) Essential airports\n5) Go back\n";
        cin >> option;
        if (option == "1") {
            string airportCode;
            cout << "Please insert the code of the airport.\n";
            cin >> airportCode;
            system.airportDetails(airportCode);
        } else if (option == "2") {
            int k;
            cout << "How many airports do you want to see?\n";
            cin >> k;
            vector<pair<Airport, int>> res = system.topKAirportsMaxFlights(k);
            for (auto i: res) {
                cout << i.first << " with " << i.second << " flights\n";
            }
        } else if (option == "3") {
            int k;
            string airportCode;
            cout << "Please insert the code of the airport.\n";
            cin >> airportCode;
            cout
                    << "How many layovers do you want to consider? (-1 for global, 0 for direct flights, 1 for 1 layover, ...)\n";
            cin >> k;
            if (k == -1) {
                set<Airport> auxAirports;
                set<string> auxCountries;
                set<string> auxCities;
                vector<int> res = system.getNumberOfDestinations(airportCode, auxAirports, auxCountries, auxCities);
                cout << "There are " << res[0] << " available destinations in " << res[2] << " different cities and "
                     << res[1] << " different countries.\n";
            } else {
                set<Airport> auxAirports;
                set<string> auxCountries;
                set<string> auxCities;
                vector<int> res = system.getNumberOfDestinationsInXLayovers(airportCode, auxAirports, auxCountries,
                                                                            auxCities, k);
                cout << "There are " << res[0] << " available destinations in " << res[2] << " different cities and "
                     << res[1] << " different countries considering at most " << k << " layovers.\n";
            }

        } else if (option == "4") {
            set<Airport> essentialAirports = system.essentialAirports();
            cout << "There are " << essentialAirports.size()
                 << " essential airports (airports are essential if, when removed, areas of the network start to be unreachable).\n";
            int n;
            cout << "How many essential airports do you wish to see?\n";
            cin >> n;
            for (auto airport: essentialAirports) {
                if (n == 0) {
                    break;
                }
                n--;
                cout << airport << endl;
            }
        } else if (option == "5") {
            break;
        } else {
            cout << "Invalid option, please choose again.\n";
        }

    }
}

void Menu::flightStatisticsMenu() {
    string option;
    while (true) {
        cout << "\nWhat do you want to do?.\n";
        cout << "1) Longest trip possible\n2) Go back\n";
        cin >> option;
        if (option == "1") {
            pair<set<pair<Airport, Airport>>, int> longestTrip = system.maxTripWithSourceDest();
            cout << "There are " << longestTrip.first.size() << " trips with the maximum amount of stops ("
                 << longestTrip.second << "):\n";
            for (pair<Airport, Airport> trip: longestTrip.first) {
                cout << "\n\tFrom " << trip.first.getName() << " (" << trip.first.getCode() << ") located in "
                     << trip.first.getCity() << ", " << trip.first.getCountry() << endl;
                cout << "\tTo " << trip.second.getName() << " (" << trip.second.getCode() << ") located in "
                     << trip.second.getCity() << ", " << trip.second.getCountry() << endl;
            }
        } else if (option == "2") {
            break;
        } else {
            cout << "Invalid option, please choose again.\n";
        }
    }

}
