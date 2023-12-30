#include <iostream>
#include "Application.h"
#include <string>

int main() {
    Application app;


    app.bestFlightOption({"-35,149",3},{"39,-94",3});

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
                    std::cout << "|3. Total Number of Airlines                           |" << std::endl;
                    std::cout << "|0. Leave                                               |" << std::endl;
                    std::cout << "|                                                      |" << std::endl;
                    std::cout << "¡......................................................¡" << std::endl;
                    std::cin >> key1;
                    switch (key1) {
                        case 1:
                            app.globalStatistics(1);
                            break;
                        case 2:
                            app.globalStatistics(2);
                            break;
                        case 3:
                            app.globalStatistics(3);
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
                    std::cout << "|0. Leave                                              |" << std::endl;
                    std::cout << "|                                                      |" << std::endl;
                    std::cout << "¡......................................................¡" << std::endl;
                    std::cin >> key2;
                    switch (key2) {
                        case 1: {
                            std::string airportCode;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cout << "|                 Flights Per Airport                  |" << std::endl;
                            std::cout << "|                                                      |" << std::endl;
                            std::cout << "|              PLEASE ENTER AIRPORT CODE:              |" << std::endl;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cin >> airportCode;
                            app.flightsFromAirport(airportCode);
                            break;
                        }
                        case 2: {
                            int subkey;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cout << "|              Flights Per City/Airline                |" << std::endl;
                            std::cout << "|                                                      |" << std::endl;
                            std::cout << "|1. Flights Leaving Per City                           |" << std::endl;
                            std::cout << "|2. Flights Arriving Per City                          |" << std::endl;
                            std::cout << "|3. Flights Per Airline                                |" << std::endl;
                            std::cout << "|                                                      |" << std::endl;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cin >> subkey;
                            if (subkey == 1) {
                                std::string cityName;
                                std::cout << "Enter City Name: ";
                                std::cin >> cityName;
                                app.flightsLeavingPerCity(cityName);
                            }
                            else if (subkey == 2) {
                                std::string cityName;
                                std::cout << "Enter Airline Name: ";
                                std::cin >> cityName;
                                app.flightsArrivingPerCity(cityName);
                            }

                            else if (subkey == 3) {
                                std::string airlineName;
                                std::cout << "Enter Airline Name: ";
                                std::cin >> airlineName;
                                app.flightsPerAirline(airlineName);

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

                            } else if (subkey == 2) {
                                std::cout << "Enter Airport Name: ";
                                std::cin >> name;
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
                            app.reachableDestinations(airportName,stops);
                            break;
                        }
                        case 2:
                            app.maximumTrip();
                            break;
                        case 3: {
                            int k;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cout << "|       Top-K Airports with Greatest Air Traffic       |" << std::endl;
                            std::cout << "|                                                      |" << std::endl;
                            std::cout << "|                    PLEASE ENTER K:                   |" << std::endl;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cin >> k;

                            app.greatestAirtraffic(k);
                            break;
                        }
                        case 4:
                            app.essencialAirports();
                            break;
                        case 0: {
                            key3 = 0;
                            break;
                        }

                    }
                    break;
                }

            }
        }
    }
}

