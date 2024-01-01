#include <iostream>
#include "Application.h"
#include <string>

int main() {
    Application app;
    int key = -1;
    while (key != 0) {
        std::cout << "¡......................................................¡" << std::endl;
        std::cout << "|            Flight Management System Menu             |" << std::endl;
        std::cout << "|                                                      |" << std::endl;
        std::cout << "|1. Global Network Statistics                          |" << std::endl;
        std::cout << "|2. Detailed Flight Statistics                         |" << std::endl;
        std::cout << "|3. Advanced Analysis                                  |" << std::endl;
        std::cout << "|4. Best Flight Option                                 |" << std::endl;
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
                    std::cout << "|0. Leave                                              |" << std::endl;
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
                            std::cout << "¡......................................................¡"<< std::endl;
                            std::cout << "|                 NOT A VALID KEY                      |"<< std::endl;
                            std::cout << "¡......................................................¡"<< std::endl;
                            break;
                        }
                    }
                }
                break;
            }

            case 2:
            {
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

                        case 1:
                        {
                            std::string airportCode;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cout << "|                 Flights Per Airport                  |" << std::endl;
                            std::cout << "|                                                      |" << std::endl;
                            std::cout << "|              PLEASE ENTER AIRPORT :                  |" << std::endl;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cin >> airportCode;
                            if(app.validateData(airportCode))app.flightsFromAirport(airportCode);

                            else
                            {
                                std::cout << "¡......................................................¡" << std::endl;
                                std::cout << "|                 NOT A VALID AIRPORT                  |" << std::endl;
                                std::cout << "¡......................................................¡" << std::endl;

                            }
                            break;
                        }

                        case 2:
                        {
                            int subkey = -1;
                            while(subkey != 0)
                            {
                                std::cout << "¡......................................................¡" << std::endl;
                                std::cout << "|              Flights Per City/Airline                |" << std::endl;
                                std::cout << "|                                                      |" << std::endl;
                                std::cout << "|1. Flights Leaving Per City                           |" << std::endl;
                                std::cout << "|2. Flights Arriving Per City                          |" << std::endl;
                                std::cout << "|3. Flights Per Airline                                |" << std::endl;
                                std::cout << "|0. Leave                                              |" << std::endl;
                                std::cout << "|                                                      |" << std::endl;
                                std::cout << "¡......................................................¡" << std::endl;
                                std::cin >> subkey;

                                if (subkey == 1)
                                {
                                    std::string cityName;
                                    std::cout << "Enter City Name: ";
                                    std::cin >> cityName;
                                    if (app.validateData(cityName))app.flightsLeavingPerCity(cityName);
                                    else {
                                        std::cout << "¡......................................................¡"<< std::endl;
                                        std::cout << "|                 NOT A VALID CITY                     |"<< std::endl;
                                        std::cout << "¡......................................................¡"<< std::endl;
                                    }
                                }

                                else if (subkey == 2) {
                                    std::string cityName;
                                    std::cout << "Enter Airline Name: ";
                                    std::cin >> cityName;
                                    if (app.validateData(cityName))
                                    {
                                        app.flightsArrivingPerCity(cityName);
                                        break;
                                    }
                                    else {
                                        std::cout << "¡......................................................¡"<< std::endl;
                                        std::cout << "|                 NOT A VALID CITY                     |"<< std::endl;
                                        std::cout << "¡......................................................¡"<< std::endl;
                                    }
                                }

                                else if (subkey == 3) {
                                    std::string airlineName;
                                    std::cout << "Enter Airline Name: ";
                                    std::cin >> airlineName;
                                    if (app.validateData(airlineName)) {
                                        app.flightsPerAirline(airlineName);
                                        break;
                                    }
                                }
                                else if (subkey == 0)  break;
                                else
                                {
                                    std::cout << "¡......................................................¡"<< std::endl;
                                    std::cout << "|                 NOT A VALID KEY                      |"<< std::endl;
                                    std::cout << "¡......................................................¡"<< std::endl;
                                }
                            }
                            break;
                        }

                        case 0: {
                            key2 = 0;
                            break;
                        }

                        default: {
                            std::cout << "¡......................................................¡"<< std::endl;
                            std::cout << "|                 NOT A VALID KEY                      |"<< std::endl;
                            std::cout << "¡......................................................¡"<< std::endl;
                            break;
                        }
                    }
                }
                break;
            }

            case 3: {
                int key3 = -1;
                while (key3 != 0)
                {
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
                            if(app.validateData(airportName))app.reachableDestinations(airportName,stops);
                            else
                            {
                                std::cout << "¡......................................................¡" << std::endl;
                                std::cout << "|                 NOT A VALID AIRPORT                  |" << std::endl;
                                std::cout << "¡......................................................¡" << std::endl;
                            }
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
                        {
                            app.essencialAirports();
                            break;
                        }

                        case 0: {
                            key3 = 0;
                            break;
                        }
                        default:
                        {
                            std::cout << "¡......................................................¡"<< std::endl;
                            std::cout << "|                 NOT A VALID KEY                      |"<< std::endl;
                            std::cout << "¡......................................................¡"<< std::endl;
                            break;
                        }

                    }
                    break;
                }
                break;

            }

            case 4:
            {
                int sourceType = -1;
                std::string source;
                std::cout << "¡......................................................¡" << std::endl;
                std::cout << "|                  Type of source:                     |" << std::endl;
                std::cout << "|                                                      |" << std::endl;
                std::cout << "|1. Airport                                            |" << std::endl;
                std::cout << "|2. City                                               |" << std::endl;
                std::cout << "|3. Geographical coordinates                           |" << std::endl;
                std::cout << "¡......................................................¡" << std::endl;
                std::cin >> sourceType;
                std::cout << "¡......................................................¡" << std::endl;
                std::cout << "|               INSERT THE SOURCE :                    |" << std::endl;
                std::cout << "¡......................................................¡" << std::endl;
                std::cin >> source;

                int destType = -1;
                std::string dest;
                std::cout << "¡......................................................¡" << std::endl;
                std::cout << "|                  Type of destination:                |" << std::endl;
                std::cout << "|                                                      |" << std::endl;
                std::cout << "|1. Airport                                            |" << std::endl;
                std::cout << "|2. City                                               |" << std::endl;
                std::cout << "|3. Geographical coordinates                           |" << std::endl;
                std::cout << "¡......................................................¡" << std::endl;
                std::cin >> destType;
                std::cout << "¡......................................................¡" << std::endl;
                std::cout << "|               INSERT THE DESTINATION :               |" << std::endl;
                std::cout << "¡......................................................¡" << std::endl;
                std::cin >> dest;
                int key4 = -1;
                std::cout << "¡......................................................¡" << std::endl;
                std::cout << "|                  Best Flight                         |" << std::endl;
                std::cout << "|                                                      |" << std::endl;
                std::cout << "|1. No filter                                          |" << std::endl;
                std::cout << "|2. Choose Airlines                                    |" << std::endl;
                std::cout << "|3. Less Airlines                                      |" << std::endl;
                std::cout << "¡......................................................¡" << std::endl;
                std::cin >> key4;

                switch (key4)
                {
                    case 1:
                    {
                        if(destType>0&&destType<4 && sourceType>0 && sourceType<4)
                            if(app.validateData(source)&&app.validateData(dest))
                                app.bestFlightOption({source,sourceType},{dest,destType});

                        break;

                    }

                    case 2:
                    {
                        int airlineCount = 0;
                        std::cout << "¡......................................................¡" << std::endl;
                        std::cout << "|               INSERT NUMBER OF AIRLINES :            |" << std::endl;
                        std::cout << "¡......................................................¡" << std::endl;
                        std::cin >> airlineCount;
                        std::vector<std::string> res;
                        std::string airline;
                        int count = 0;
                        while(count < airlineCount)
                        {
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cout << "|               INSERT AIRLINE :                      |" << std::endl;
                            std::cout << "¡......................................................¡" << std::endl;
                            std::cin >> airline;
                            res.push_back(airline);
                            count++;
                        }
                        if(destType>0&&destType<4 && sourceType>0 && sourceType<4)
                            if(app.validateData(source)&&app.validateData(dest))
                                app.bestFlightOptionAirline({source,sourceType},{dest,destType},res);
                    }
                    case 3:
                    {
                        //add later

                    }

                    default:
                    {
                        std::cout << "¡......................................................¡"<< std::endl;
                        std::cout << "|                 NOT A VALID KEY                      |"<< std::endl;
                        std::cout << "¡......................................................¡"<< std::endl;
                        break;
                    }
                }

            }
        }
    }
}

