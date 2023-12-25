//
// Created by tiagomonteiro on 12/20/23.
//

#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include <algorithm>
#include "Application.h"
#include "Airport.h"
#include "Flight.h"

Application::Application()
{
    std::ifstream in("airports.csv");
    std::string line;
    std::getline(in, line, '\n'); // taking out the first line;
    while (std::getline(in, line, '\n'))
    {

        std::istringstream iss(line);
        std::string word;
        std::vector<std::string> lista;

        std::getline(iss, word, ','); //CODE
        lista.push_back(word);

        std::getline(iss, word, ','); //NAME
        lista.push_back(word);

        std::getline(iss, word, ',');//CITY
        lista.push_back(word);

        std::getline(iss, word, ',');//COUNTRY
        lista.push_back(word);

        std::getline(iss, word, ',');//LAT
        lista.push_back(word);

        std::getline(iss, word, ',');//LONG
        lista.push_back(word);

        float latitude = std::stof(lista[4]);
        float longitude = std::stof(lista[5]);

        Airport airport(lista[0], lista[1], lista[2], lista[3], latitude, longitude);
        airports.insert(airport);
        graph.addAirport(airport);
    }

    std::ifstream in1("airlines.csv");
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
        airlines[words[0]] = airline;
    }

    std::ifstream in2("flights.csv");
    std::getline(in2, line, '\n');
    int i = 0;
    while (std::getline(in2, line, '\n')){

        std::istringstream iss(line);
        std::vector<std::string> words(3);
        std::getline(iss, words[0], ','); //source code
        std::getline(iss, words[1], ','); //dest code
        std::getline(iss, words[2], ','); //airline code
        ;

        auto source = graph.findAirport(words[0]);
        auto dest = graph.findAirport(words[1]);
        auto airline = airlines.find(words[2]);

        graph.addFlight(source,dest,airline->second);

    }

    std::cout << "parse done"<<std::endl;
}


void Application::numberOfAirports()
{
    std::cout << "Global number of airports: "<< airports.size() <<std::endl;
    std::cout << "Global number of airlines: " << airlines.size() << std::endl;

}

void Application::flightsFromAirport(std::string airport) //expand later to get more particular data, maybe?
{
    std::set<std::string> differentAirlines;
    std::set<std::string> differentCities;
    std::set<std::string> differentCountries;
    std::map<std::string, std::vector<Airline>> trackAirlines;

    auto thisAirport = graph.findAirport(airport);
    std::cout << "From " << thisAirport->getName() << " we have the following destinations done for the following airlines:"<<std::endl;

    for(auto flight:thisAirport->getFlights())
    {
        differentAirlines.insert(flight.getAirline().getCode());
        differentCities.insert(flight.getDest()->getCity());
        differentCountries.insert(flight.getDest()->getCountry());
        auto itAirline = trackAirlines.find(flight.getDest()->getName());

        if (itAirline != trackAirlines.end()) itAirline->second.push_back(flight.getAirline());

        else
        {
            std::vector<Airline> v;
            v.push_back(flight.getAirline());
            trackAirlines.insert({flight.getDest()->getName(), v});
        }

    }
    for(auto pair: trackAirlines)
    {
        std::cout << pair.first << ": ";
        for(auto airlines: pair.second)
        {
            std::cout << airlines.getName() << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << differentCities.size() << " different cities are reachable from " << thisAirport->getName() << std::endl;
    std::cout << differentCountries.size() << " different cities are reachable from " << thisAirport->getName() << std::endl;
    std::cout << trackAirlines.size() << " different airports are reachable from " << thisAirport->getName() << std::endl;
    std::cout << differentAirlines.size() << " airlines operate from " << thisAirport->getName() << std::endl;

}

void Application::flightsLeavingPerCity()
{
    std::map<std::string, int> cityFlightCount;

    for (auto airport : graph.getAirports())
    {
        for(auto flight: airport.second->getFlights()) //flights leaving the city
        {
            auto it = cityFlightCount.find(airport.second->getCity());
            if (it != cityFlightCount.end())
            {
                it->second++;
            }
            else
            {
                cityFlightCount.insert({airport.second->getCity(), 1});
            }
        }

    }

    std::vector<std::pair<std::string, int>> sortedCities(cityFlightCount.begin(), cityFlightCount.end());
    std::sort(sortedCities.begin(), sortedCities.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // LATER ADD A MENU ASKING FOR HOW MANY VALUES DO YOU WANT, SO WE DONT HAVE TO PRINT EVERYTHING!

    std::cout << "Flights leaving per City (Descending order):" << std::endl;
    int i = 0;
    for (const auto& entry : sortedCities)
    {
        std::cout << entry.first << ": " << entry.second << " flights" << std::endl;
        i+=entry.second;
    }
    std::cout << "total: " << i;
}


void Application::flightsArrivingPerCity()
{
    std::map<std::string, int> cityFlightCount;

    for (auto airport : graph.getAirports())
    {
        for(auto flight: airport.second->getFlights()) //flights leaving the city
        {
            auto it = cityFlightCount.find(flight.getDest()->getCity());
            if (it != cityFlightCount.end())
            {
                it->second++;
            }
            else
            {
                cityFlightCount.insert({flight.getDest()->getCity(), 1});
            }
        }

    }

    std::vector<std::pair<std::string, int>> sortedCities(cityFlightCount.begin(), cityFlightCount.end());
    std::sort(sortedCities.begin(), sortedCities.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // LATER ADD A MENU ASKING FOR HOW MANY VALUES DO YOU WANT, SO WE DONT HAVE TO PRINT EVERYTHING!

    std::cout << "Flights arriving per City (Descending order):" << std::endl;
    int i = 0;
    for (const auto& entry : sortedCities)
    {
        std::cout << entry.first << ": " << entry.second << " flights" << std::endl;
        i+=entry.second;
    }
    std::cout << "total: " << i;
}

void Application::flightsPerAirline()
{
    std::map<std::string, int> cityFlightCount;

    for (auto airport : graph.getAirports())
    {
        for(auto flight: airport.second->getFlights()) //flights leaving the city
        {
            auto it = cityFlightCount.find(flight.getAirline().getName());
            if (it != cityFlightCount.end())
            {
                it->second++;
            }
            else
            {
                cityFlightCount.insert({flight.getAirline().getName(), 1});
            }
        }

    }

    std::vector<std::pair<std::string, int>> sortedCities(cityFlightCount.begin(), cityFlightCount.end());
    std::sort(sortedCities.begin(), sortedCities.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // LATER ADD A MENU ASKING FOR HOW MANY VALUES DO YOU WANT, SO WE DONT HAVE TO PRINT EVERYTHING!

    std::cout << "Total number of flights each airline has (Descending order):" << std::endl;
    int i = 0;
    for (const auto& entry : sortedCities)
    {
        std::cout << entry.first << ": " << entry.second << " flights" << std::endl;
        i+=entry.second;
    }
    std::cout << "total: " << i;
}

void Application::reachableDestinations(std::string airport,int n)
{
    std::set<std::string> differentAirports;
    std::set<std::string> differentCountries;
    std::set<std::string> differentCities;
    for(auto airport: graph.getAirports()) airport.second->setVisited(false);
    auto source = graph.findAirport(airport);
    std::queue<std::pair<Airport*,int>> q;
    q.push({source,0});
    source->setVisited(true);
    while(!q.empty())
    {
        auto current = q.front();
        q.pop();
        differentAirports.insert(current.first->getName());
        differentCities.insert(current.first->getCity());
        differentCountries.insert(current.first->getCountry());
        if(current.second <  n)
        {
            for(auto flight: current.first->getFlights())
            {
                if(!flight.getDest()->isVisited())
                {
                    q.push({flight.getDest(),current.second+1});
                    flight.getDest()->setVisited(true);
                }
           }
        }
    }

    std::cout << "Different countries: "<< differentCountries.size() << std::endl;
    std::cout << "Different cities: "<< differentCities.size() << std::endl;
    std::cout << "Different airports: "<< differentAirports.size() << std::endl;


}
void Application::maximumTrip() {