#include <iostream>
#include <string>

class Application {
public:
    // Global Network Statistics
    void showTotalNumberOfAirports() {
        // Logic to display the total number of airports
    }

    void showTotalNumberOfFlights() {
        // Logic to display the total number of flights
    }

    // Detailed Flight Statistics
    void showFlightsPerAirport(const std::string& airportName) {
        // Logic to display flights per specified airport
    }

    void showFlightsPerCity(const std::string& cityName) {
        // Logic to display flights per specified city
    }

    void showFlightsPerAirline(const std::string& airlineName) {
        // Logic to display flights per specified airline
    }

    void showDistinctCountriesPerAirportOrCity(const std::string& name, bool isCity) {
        // Logic to display distinct countries per airport or city
    }

    void showDestinationsPerAirport(const std::string& airportName) {
        // Logic to display destinations per specified airport
    }

    // Advanced Analysis
    void showReachableDestinations(const std::string& airportName, int stops) {
        // Logic to display reachable destinations from a specified airport with a given number of stops
    }

    void showMaximumTripAndAirports() {
        // Logic to display the maximum trip and corresponding airports
    }

    void showTopKAirports(int k) {
        // Logic to display the top-K airports with the greatest air traffic
    }

    void showEssentialAirportsForNetwork() {
        // Logic to display essential airports for network circulation
    }

    // Additional methods as required for other functionalities
};


int main() {
    Application application;
    int key = -1;

    while (key != 0) {
        std::cout << "¡......................................................¡" << std::endl;
        std::cout << "|            Flight Management System Menu             |" << std::endl;
        std::cout << "|                                                      |" << std::endl;
        std::cout << "|1. Global Network Statistics                          |" << std::endl;
        std::cout << "|2. Detailed Flight Statistics                         |" << std::endl;
        std::cout << "|3. Advanced Analysis                                  |" << std::endl;
        std::cout << "|0. Exit                                               |" << std::endl;
        std::cout << "|                                                      |" << std::endl;
        std::cout << "!......................................................!" << std::endl;
        // ... Menu options
        std::cin >> key;

        switch (key) {
            case 1: {
                int key1 = -1;
                while (key1 != 0) {
                    std::cout << "¡......................................................¡" << std::endl;
                    std::cout << "|              Global Network Statistics               |" << std::endl;
                    std::cout << "|                                                      |" << std::endl;
                    std::cout << "|1. Total Number of Airports                           |" << std::endl;
                    std::cout << "|2. Total Number of Flights                            |" << std::endl;
                    std::cout << "|0.Leave                                               |" << std::endl;
                    std::cout << "|                                                      |" << std::endl;
                    std::cout << "¡......................................................¡" << std::endl;
                    std::cin >> key1;
                    switch (key1) {
                        case 1:
                            application.showTotalNumberOfAirports();
                            break;
                        case 2:
                            application.showTotalNumberOfFlights();
                            break;
                        case 0: {
                            key1 = 0;
                            break;
                        }
                        default: {
                            std::cout << "¡....................................¡" << std::endl;
                            std::cout << "|     Please insert a valid key!     |" << std::endl;
                            std::cout << "!....................................!" << std::endl;
                            break;
                        }
                    }
                }
                break;
            }
            case 2: {
                int key2 = -1;
                while (key2 != 0) {
                    std::cout << "¡......................................................¡" << std::endl;
                    std::cout << "|              Detailed Flight Statistics              |" << std::endl;
                    std::cout << "|                                                      |" << std::endl;
                    std::cout << "|1. Flights Per Airport                                |" << std::endl;
                    std::cout << "|2. Flights Per City/Airline                           |" << std::endl;
                    std::cout << "|3. Distinct Countries Per Airport/City                |" << std::endl;
                    std::cout << "|4. Destinations Per Airport                           |" << std::endl;
                    std::cout << "|0. Leave                                              |" << std::endl;
                    std::cout << "|                                                      |" << std::endl;
                    std::cout << "¡......................................................¡" << std::endl;
                    std::cin >> key2;
                    switch (key2) {
                        case 1: {
                            std::string airportName;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cout << "|                 Flights Per Airport                  |" << std::endl;
                            std::cout << "|                                                      |" << std::endl;
                            std::cout << "|              PLEASE ENTER AIRPORT NAME:              |" << std::endl;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cin >> airportName;
                            application.showFlightsPerAirport(airportName);
                            break;
                        }
                        case 2: {
                            int subkey;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cout << "|              Flights Per City/Airline                |" << std::endl;
                            std::cout << "|                                                      |" << std::endl;
                            std::cout << "|1. Flights Per City                                   |" << std::endl;
                            std::cout << "|2. Flights Per Airline                                |" << std::endl;
                            std::cout << "|                                                      |" << std::endl;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cin >> subkey;
                            if (subkey == 1) {
                                std::string cityName;
                                std::cout << "Enter City Name: ";
                                std::cin >> cityName;
                                application.showFlightsPerCity(cityName);
                            } else if (subkey == 2) {
                                std::string airlineName;
                                std::cout << "Enter Airline Name: ";
                                std::cin >> airlineName;
                                application.showFlightsPerAirline(airlineName);
                            }
                            break;
                        }
                        case 3: {
                            int subkey;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cout << "|         Distinct Countries Per Airport/City          |" << std::endl;
                            std::cout << "|                                                      |" << std::endl;
                            std::cout << "|1. Distinct Countries Per City                        |" << std::endl;
                            std::cout << "|2. Distinct Countries Per Airline                     |" << std::endl;
                            std::cout << "|                                                      |" << std::endl;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cin >> subkey;
                            std::string name;
                            if (subkey == 1) {
                                std::cout << "Enter City Name: ";
                                std::cin >> name;
                                application.showDistinctCountriesPerAirportOrCity(name, true);
                            } else if (subkey == 2) {
                                std::cout << "Enter Airport Name: ";
                                std::cin >> name;
                                application.showDistinctCountriesPerAirportOrCity(name, false);
                            }
                            break;
                        }
                        case 4: {
                            std::string airportName;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cout << "|              Destinations Per Airport                |" << std::endl;
                            std::cout << "|                                                      |" << std::endl;
                            std::cout << "|              PLEASE ENTER AIRPORT NAME:              |" << std::endl;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cin >> airportName;
                            application.showDestinationsPerAirport(airportName);
                            break;
                        }

                        case 0: {
                            key2 = 0;
                            break;
                        }

                        default: {
                            std::cout << "¡....................................¡" << std::endl;
                            std::cout << "|     Please insert a valid key!     |" << std::endl;
                            std::cout << "!....................................!" << std::endl;
                            break;
                        }
                    }
                }
                break;
            }
            case 3: {
                int key3 = -1;
                while (key3 != 0) {
                    std::cout << "¡......................................................¡" << std::endl;
                    std::cout << "|                  Advanced Analysis                   |" << std::endl;
                    std::cout << "|                                                      |" << std::endl;
                    std::cout << "|1. Reachable Destinations from Airport with X Stops   |" << std::endl;
                    std::cout << "|2. Maximum Trip and Corresponding Airports            |" << std::endl;
                    std::cout << "|3. Top-K Airports with Greatest Air Traffic           |" << std::endl;
                    std::cout << "|4. Essential Airports for Network Circulation         |" << std::endl;
                    std::cout << "|0. Leave                                              |" << std::endl;
                    std::cout << "|                                                      |" << std::endl;
                    std::cout << "!......................................................!" << std::endl;
                    std::cin >> key3;
                    switch (key3) {
                        case 1: {
                            std::string airportName;
                            int stops;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cout << "|   Reachable Destinations from Airport with X Stops   |" << std::endl;
                            std::cout << "|                                                      |" << std::endl;
                            std::cout << "|              PLEASE ENTER AIRPORT NAME:              |" << std::endl;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cin >> airportName;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cout << "|   Reachable Destinations from Airport with X Stops   |" << std::endl;
                            std::cout << "|                                                      |" << std::endl;
                            std::cout << "|                    PLEASE ENTER X:                   |" << std::endl;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cin >> stops;
                            application.showReachableDestinations(airportName, stops);
                            break;
                        }
                        case 2:
                            application.showMaximumTripAndAirports();
                            break;
                        case 3: {
                            int k;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cout << "|       Top-K Airports with Greatest Air Traffic       |" << std::endl;
                            std::cout << "|                                                      |" << std::endl;
                            std::cout << "|                    PLEASE ENTER K:                   |" << std::endl;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cin >> k;
                            application.showTopKAirports(k);
                            break;
                        }
                        case 4:
                            application.showEssentialAirportsForNetwork();
                            break;
                        case 0: {
                            key3 = 0;
                            break;
                        }
                }
                break;
            }
            default: {
                std::cout << "¡....................................¡" << std::endl;
                std::cout << "|     Please insert a valid key!     |" << std::endl;
                std::cout << "!....................................!" << std::endl;
                break;
            }
        }
    }