//
// Created by tiagomonteiro on 12/20/23.
//

#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include "Application.h"
#include "Airport.h"
#include "Flight.h"

Application::Application()
{
    std::ifstream in("../csv/airports.csv");
    std::string line;
    std::getline(in, line, '\n'); // taking out the first line;
    while (std::getline(in, line, '\n'))
    {

        std::istringstream iss(line);
        std::string word;
        std::vector<std::string> lista;

        std::getline(iss, word, ',');
        lista.push_back(word);

        std::getline(iss, word, ',');
        lista.push_back(word);

        std::getline(iss, word, ',');
        lista.push_back(word);

        std::getline(iss, word, ',');
        lista.push_back(word);

        std::getline(iss, word, ',');
        lista.push_back(word);

        std::getline(iss, word, ',');
        lista.push_back(word);

        float latitude = std::stof(lista[4]);
        float longitude = std::stof(lista[5]);

        Airport airport(lista[0], lista[1], lista[2], lista[3], latitude, longitude);
        airports.insert(airport);
        graph.addAirport(airport);
    }


    std::ifstream in1("../csv/airlines.csv");
    std::getline(in1, line, '\n');
    while (std::getline(in1, line, '\n'))
    {
        std::istringstream iss(line);
        std::vector<std::string> words(4);
        std::getline(iss, words[0], ',');
        std::getline(iss, words[1], ',');
        std::getline(iss, words[2], ',');
        std::getline(iss, words[3], ',');
        Airline airline(words[0], words[1], words[2], words[3]);
        airlines.insert(airline);
    }

    std::ifstream in2("../csv/flights.csv");
    std::getline(in2, line, '\n');
    int i = 0;
    while (std::getline(in2, line, '\n')){

        std::istringstream iss(line);
        std::vector<std::string> words(3);
        std::getline(iss, words[0], ','); //source code
        std::getline(iss, words[1], ','); //dest code
        std::getline(iss, words[2], ','); //airline code

        Airport* source;
        Airport* dest;
        Airline theAirline;

        for(auto airport: airports)
        {
            if(airport.getCode() == words[0])
                source = new Airport(airport);

            if(airport.getCode() == words[1])
                dest = new Airport(airport);

        }

        for(auto airline: airlines)
        {
            if(airline.getCode() == words[2])
            {
                theAirline = airline;
            }
        }
        graph.addFlight(source,dest,theAirline);
        i++;
    }


}

void Application::getVertex()
{
    for(auto airport: graph.getAirportsSet())
    {
        std::cout << airport->getCode() << ": ";
        for(auto flight: airport->getFlights())
        {
            std::cout << flight.getDest()->getCode() << " (" << flight.getAirline().getCode() << ")  ";
        }
        std::cout << std::endl;
    }

}
