#include "Menu.h"

Menu::Menu(const ManagementSystem &system) : system(system) {}

void Menu::start() {
    string option;
    cout << "Hello, welcome to the flight database!\n";
    while (true) {
        cout << "\nWhat do you want to do?\n";
        cout << "1) Get statistics about the flight network.\n2) Search for a flight\n";
        cin >> option;
        if (option == "1") {
            statisticsMenu();
        } else if (option == "2") {
            cout << "searching for flights...\n";
        } else {
            cout << "Invalid option, please choose again.\n";
        }
    }
}

void Menu::statisticsMenu() {
    string option;
    while (true) {
        cout << "\nWhat do you want statistics on?\n";
        cout << "1) Airports.\n2) Airlines.\n3) Flights.\n4) Cities.\n5) Countries.\n6) Go back.\n";
        cin >> option;
        if (option == "1") {
            string airport;
            cout << "Please type the code of the airport.\n";
            cin >> airport;

        } else if (option == "2") {

        } else if (option == "3") {

        } else if (option == "4") {

        } else if (option == "5") {

        } else if (option == "6") {

        } else {
            cout << "Invalid option, please choose again.\n";
        }
    }
}
