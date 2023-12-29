//
// Created by tiagomonteiro on 12/20/23.
//

#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <list>
#include <stack>
#include <climits>

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
    for(auto airpot: graph.getAirports()){
        airpot.second->setOutbound(0);
        airpot.second->setInbound(0);
    }

    for(auto airpot: graph.getAirports()){

        airpot.second->setOutbound(airpot.second->getFlights().size());
        for(auto flight: airpot.second->getFlights())
        {
            flight.getDest()->setInbound(flight.getDest()->getInbound()+1);
        }
    }

    std::cout << "parse done"<<std::endl;
}


void Application::globalStatistics(int key)
{
    int count_flights = 0;
    for(auto airport: graph.getAirports()) airport.second->setVisited(false);
    std::queue<Airport*> q;
    for(auto airport: graph.getAirports())
    {
        if(!airport.second->isVisited())
        {
            q.push(airport.second);
            airport.second->setVisited(true);
            while(!q.empty())
            {
                auto current = q.front();
                count_flights += current->getFlights().size();
                q.pop();
                for(auto flight: current->getFlights())
                {
                    if(!flight.getDest()->isVisited())
                    {
                        q.push(flight.getDest());
                        flight.getDest()->setVisited(true);
                    }
                }
            }

        }

    }

    if(key==1)std::cout << "Global number of airports: "<< airports.size() <<std::endl;
    if(key==2)std::cout << "Global number of flights: "<< count_flights <<std::endl;
    if(key==3)std::cout << "Global number of airlines: " << airlines.size() << std::endl;

}

void Application::flightsFromAirport(std::string airport) //expand later to get more particular data, maybe?
{
    std::set<std::string> differentAirlines;
    std::set<std::string> differentCities;
    std::set<std::string> differentCountries;
    int count = 0;
    std::map<std::string, std::vector<Airline>> trackAirlines;

    auto thisAirport = graph.findAirport(airport);
    std::cout << "From " << thisAirport->getName() << " we have the following destinations done by the following airlines:"<<std::endl;

    for(auto flight:thisAirport->getFlights())
    {
        count++;
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
    std::cout << count << " different flights available from " << thisAirport->getName() << std::endl;
    std::cout << differentCities.size() << " different cities are reachable from " << thisAirport->getName() << std::endl;
    std::cout << differentCountries.size() << " different cities are reachable from " << thisAirport->getName() << std::endl;
    std::cout << trackAirlines.size() << " different airports are reachable from " << thisAirport->getName() << std::endl;
    std::cout << differentAirlines.size() << " airlines operate from " << thisAirport->getName() << std::endl;

}

void Application::flightsLeavingPerCity(std::string cityName)
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

    //std::cout << "Flights leaving from " << cityName <<" :"<< std::endl;
    for (const auto& entry : sortedCities)
    {
        if(entry.first == cityName)
        {
            std::cout << entry.first << ": " << entry.second << " flights" << std::endl;
            break;
        }
    }
}


void Application::flightsArrivingPerCity(std::string City)
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

   // std::cout << "Flights arriving per City (Descending order):" << std::endl;
    for (const auto& entry : sortedCities)
    {
        if(entry.first ==  City) std::cout << entry.first << ": " << entry.second << " flights" << std::endl;
    }
}

void Application::flightsPerAirline(std::string airlineName)
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

  //  std::cout << "Total number of flights each airline has (Descending order):" << std::endl;
    for (const auto& entry : sortedCities)
    {
        if(entry.first == airlineName) std::cout << entry.first << ": " << entry.second << " flights" << std::endl;
    }
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

bool inStack(std::stack<Airport*>& s, Airport* airport) ;
void dfs_essential(Graph graph, Airport* airport, std::set<Airport*>& res, std::stack<Airport*>& s, int index);

void Application::essencialAirports() {
    std::set<Airport*> res;
    int index = 1;
    std::stack<Airport*> s;

    for (auto airport : graph.getAirports()) {
        airport.second->setLow(0);
        airport.second->setNum(0);
        airport.second->setVisited(false);
    }

    for (auto airport : graph.getAirports()) {
        if (!airport.second->getNum()) {
            dfs_essential(graph, airport.second, res, s, index);
        }
    }

    std::cout << "There are " << res.size() << " essential airports to the network." <<std::endl;
}


void dfs_essential(Graph graph, Airport* airport, std::set<Airport*>& res, std::stack<Airport*>& s, int index) {
    airport->setLow(index);
    airport->setNum(index);
    index++;
    s.push(airport);
    int children = 0;
    bool isArticulation = false;

    for (auto flight: airport->getFlights()) {

        if (!flight.getDest()->getNum()) {
            children++;
            dfs_essential(graph, flight.getDest(), res, s, index);
            airport->setLow(std::min(airport->getLow(), flight.getDest()->getLow()));

            if (flight.getDest()->getLow() >= airport->getNum()) {
                isArticulation = true;
            }
        }

        else if (inStack(s, flight.getDest())) {
            airport->setLow(std::min(airport->getLow(), flight.getDest()->getNum()));
        }
    }
        if ((!airport->getInbound() && children > 1) || (airport->getNum() > 1 && isArticulation)) {
            res.insert(airport);
        }
    s.pop();
}


bool inStack(std::stack<Airport*>& s, Airport* airport) {
    std::stack<Airport*> tempStack;

    while (!s.empty()) {
        auto current = s.top();
        s.pop();
        tempStack.push(current);

        if (current == airport) {
            while (!tempStack.empty()) {
                s.push(tempStack.top());
                tempStack.pop();
            }
            return true;
        }
    }
    while (!tempStack.empty()) {
        s.push(tempStack.top());
        tempStack.pop();
    }
    return false;
}

void Application::greatestAirtraffic(int k) {

    std::vector<std::pair<Airport*,int>> outcome;
    for(auto airport: graph.getAirports())
    {
        outcome.push_back({airport.second,airport.second->getInbound()+airport.second->getOutbound()});
    }
    std::sort(outcome.begin(), outcome.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;});

    for(auto par: outcome)
    {
        if(k == 0) break;
        std::cout << par.first->getName() << " has " << par.second << " flights"<<std::endl;
        k--;
    }
}

void Application::maximumTrip() {
    std::vector<std::pair<Airport*,Airport*>> res;
    int max = 0;
    for(auto airport: graph.getAirports()) airport.second->setVisited(false);
    for(auto airport: graph.getAirports())
    {
        if(!airport.second->isVisited())
        {
            airport.second->setVisited(true);
            auto outcome = max_distance_bfs(airport.second);
            if(outcome.second > max)
            {
                res.clear();
                max = outcome.second;
                for(auto element:outcome.first)
                {
                    res.push_back({airport.second,element});

                }
            }
            else if(outcome.second == max)
            {
                for(auto element:outcome.first)
                {
                    res.push_back({airport.second,element});

                }
            }
        }
    }
    std::cout << "The maxium trip goes through "<< max <<  " airports" <<std::endl;
    for(auto par: res)
    {
        std::cout << par.first->getName() << " ("<<par.first->getCode() << " )"<< " -> " << par.second->getName() << " ("<<par.second->getCode() << ")"<<std::endl;
    }
}

std::pair<std::vector<Airport*>,int> Application::max_distance_bfs(Airport* source)
{
    for(auto airport: graph.getAirports()) airport.second->setProcessed(false);
    std::queue<std::pair<Airport*,int>> q;
    int max = 0;
    std::vector<Airport*> airports;
    q.push({source,0});
    source->setProcessed(true);
    while(!q.empty())
    {
        auto current = q.front();
        q.pop();

        for(auto flight: current.first->getFlights()){
            if(!flight.getDest()->isProcessed())
            {
                q.push({flight.getDest(),current.second+1});
                flight.getDest()->setProcessed(true);
            }
        }
        if(current.second > max){
            airports.clear();
            airports.push_back(current.first);
            max = current.second;
        }

        else if(current.second == max) airports.push_back(current.first);
    }
    return std::make_pair(airports,max);
}

void Application::bestFlightOption(std::string source, std::string dest) {
    auto sourceAirport =  graph.findAirport(source);
    auto destAirport = graph.findAirport(dest);


}


