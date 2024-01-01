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
#include <limits>
#include "Application.h"
#include "Airport.h"

/**
 * Class Constructor reads and parses data
 * Time Complexity:O(nlog(n))
 **/
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
        auto it = cityMap.find(airport.getCity());
        if(it != cityMap.end()) it->second.push_back(airport.getCode());
        else cityMap[airport.getCity()] = {airport.getCode()};
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

}
/**
 *  Function that finds out the number of flights, airlines and airports.
 * Time complexity: O(|V| + |E|), |V| - number of vertices in the graph (airports), |E| - number of edges in the graph (flights)
 **/

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
/**
 * Function that finds out the available flights from an airport and some useful related information like different,
 * airports and countries.
 * Time Complexity: O(|V|+|E|)
 **/

void Application::flightsFromAirport(std::string airport)
{
    std::set<std::string> differentAirlines;
    std::set<std::string> differentCities;
    std::set<std::string> differentCountries;
    int count = 0;
    std::map<std::string, std::vector<Airline>> trackAirlines;
    if(airport.size() != 3) //if we get the name and not the code
    {
        for(auto dAirport: airports) if(dAirport.getName() == airport) airport = dAirport.getCode();
    }

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

/**
 * Function that finds out the number o flights leaving one city
 * Time Complexity: O(|V|+|E|)
 **/

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

/**
 * Function that finds out the number o flights arriving in one city
 * Time Complexity: O(|V|+|E|)
 **/

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


    for (const auto& entry : sortedCities)
    {
        if(entry.first ==  City) std::cout << entry.first << ": " << entry.second << " flights" << std::endl;
    }
}

/**
 * Function that finds out the number o flights an airline does
 * Time Complexity: O(|V|+|E|)
 **/

void Application::flightsPerAirline(std::string airlineName)
{
    std::map<std::string, int> cityFlightCount;
    if(airlineName.size() == 3)
        airlineName = airlines[airlineName].getName();


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
        return a.second > b.second;});

    for (const auto& entry : sortedCities)
    {
        if(entry.first == airlineName) std::cout << entry.first << ": " << entry.second << " flights" << std::endl;
    }
}

/**
 * Function that finds out given an airport and a number of layover the number of airports, cities and countries reacheable.
 * Time Complexity: O(|V|+|E|)
 **/

void Application::reachableDestinations(std::string airport,int n)
{
    std::set<std::string> differentAirports;
    std::set<std::string> differentCountries;
    std::set<std::string> differentCities;
    if(airport.size() != 3)
    {
        for(auto dAirpot:airports)
            if(dAirpot.getName() == airport) airport = dAirpot.getCode();
    }
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
/**
 * Function that finds out the essential airports to the whole system, this means that components would be separeted if we took out his airports
 * Time Complexity: O(|V|+|E|)
 **/

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

/**
 * Function that finds out the airpots that get more traffic this means more planes arriving+leaving
 * Time Complexity: O(nlog(n)) due to sort algorithm
 **/

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

/**
 * Function that finds out the diameter of the graph which means the points that are the further apart
 * In practical terms it means the airports that you need the maximum number of layovers to get to (from a source one).
 * Time Complexity: O(|V|*(|V|+|E|)
 **/
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

/**
 * Function that finds out the most effient way to get from a place to another, you might use
 *  an airport, a city or coordinates. If a city has more than one airport, you might get multiple answers
 * Time Complexity: O(|V|+|E|)
 **/

void Application::bestFlightOption(std::pair<std::string, int> source, std::pair<std::string, int> dest) {

    std::vector<Airport *> origin;
    std::vector<Airport *> destination;

    if (source.second == 1)
    {
        if(source.first.size() != 3)
        {
            for(auto airport:airports) if(airport.getName() == source.first) source.first = airport.getCode();
        }

        origin.push_back(graph.findAirport(source.first)); //Airport Code
    }

    else if (source.second == 2) // CITY
        for (auto airport : cityMap[source.first])
            origin.push_back(graph.findAirport(airport));

    else if(source.second == 3)
    {
        float lowest = std::numeric_limits<float>::max();

        for (auto airport : graph.getAirports())
        {
            float distance = airport.second->distanceToPoint(source.first);
            if (distance < lowest) {
                origin.clear();
                origin.push_back(graph.findAirport(airport.first));
                lowest = distance;
                if (lowest == 0) break; // Avoid further checks if distance is zero
            }
            else if (distance == lowest)
                origin.push_back(graph.findAirport(airport.first));
        }
    }

    if (dest.second == 1)
    {
        if(dest.first.size() != 3)
        {
            for(auto airport:airports) if(airport.getName() == dest.first) dest.first = airport.getCode();
        }
        destination.push_back(graph.findAirport(dest.first)); //Airport
    }

    else if (dest.second == 2) //CITY
        for (auto airport : cityMap[dest.first])
            destination.push_back(graph.findAirport(airport));

    else if(dest.second == 3)
    {
        float lowest = std::numeric_limits<float>::max();
        for (auto airport : graph.getAirports()) {
            float distance = airport.second->distanceToPoint(dest.first);
            if (distance < lowest) {
                destination.clear();
                destination.push_back(graph.findAirport(airport.first));
                lowest = distance;
                if (lowest == 0) break; // Avoid further checks if distance is zero
            }
            else if (distance == lowest)
                destination.push_back(graph.findAirport(airport.first));
        }
    }

    for (auto &airport : graph.getAirports()) {
        airport.second->setVisited(false);
        airport.second->setStopCount(INT_MAX);
    }

    std::queue<std::pair<Airport *, std::vector<Airport *>>> q;


    for (auto &startAirport : origin) {
        std::vector<Airport *> startRoute = {startAirport};
        q.push({startAirport, startRoute});
        startAirport->setVisited(true);
        startAirport->setStopCount(0);
    }

    std::vector<std::vector<Airport *>> allRoutes;
    int minStops = INT_MAX;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        Airport *currentAirport = current.first;
        std::vector<Airport *> currentRoute = current.second;

        for (auto flight : currentAirport->getFlights()) {
            if (!flight.getDest()->isVisited())
            {
                flight.getDest()->setVisited(true);
                flight.getDest()->setStopCount(currentAirport->getStopCount() + 1);

                std::vector<Airport *> newRoute = currentRoute;
                newRoute.push_back(flight.getDest());

                q.push({flight.getDest(), newRoute});

                if (std::find(destination.begin(), destination.end(), flight.getDest()) != destination.end())
                {
                    if (flight.getDest()->getStopCount() < minStops) {
                        allRoutes.clear();
                        minStops = flight.getDest()->getStopCount();
                    }

                    if (flight.getDest()->getStopCount() == minStops) {
                        allRoutes.push_back(newRoute);
                    }
                }
            }
        }
    }

    std::cout << "Minimum stops to reach destination: " << minStops << std::endl;
    std::cout << "All routes with minimum stops:" << std::endl;
    for (auto &route : allRoutes) {
        auto routeSize = route.size();
        for (auto i = 0; i < routeSize; ++i) {
            std::cout << route[i]->getName() << "(" << route[i]->getCode() << ")";
            if (i < routeSize - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
}

/**
 * Function that finds out the most effient way to get from a place to another, you might use
 *  an airport, a city or coordinates but adds a filter with the only airlines that we are allowed to use.
 * Time Complexity: O(|V|+|E|)
 **/

void Application::bestFlightOptionAirline(std::pair<std::string, int> source, std::pair<std::string, int> dest, std::vector<std::string> chosenAirlines) {
    std::vector<Airport *> origin;
    std::vector<Airport *> destination;
    std::set<Airline> availableAirlines;

    for (auto airline : chosenAirlines) availableAirlines.insert(airlines[airline]);

    if (source.second == 1)
    {
        if(source.first.size() != 3)
        {
            for(auto airport:airports) if(airport.getName() == source.first) source.first = airport.getCode();
        }
        origin.push_back(graph.findAirport(source.first)); //Airport Code
    }

    else if (source.second == 2) // CITY
        for (auto airport : cityMap[source.first])
            origin.push_back(graph.findAirport(airport));
    else
    {
        auto lowest = std::numeric_limits<float>::max();

        for (auto airport : graph.getAirports()) {
            auto distance = airport.second->distanceToPoint(source.first);
            if (distance < lowest) {
                origin.clear();
                origin.push_back(graph.findAirport(airport.first));
                lowest = distance;
                if (lowest == 0) break; // Avoid further checks if distance is zero
            }
            else if (distance == lowest) origin.push_back(graph.findAirport(airport.first));
        }
    }

    if (dest.second == 1)
    {
        if(dest.first.size() != 3)
        {
            for(auto airport:airports) if(airport.getName() == dest.first) dest.first = airport.getCode();
        }
        destination.push_back(graph.findAirport(dest.first)); //Airport
    }

    else if (dest.second == 2) // CITY
        for (auto airport : cityMap[dest.first])
            destination.push_back(graph.findAirport(airport));

    else
    {
        auto lowest = std::numeric_limits<float>::max();
        for (auto airport : graph.getAirports())
        {
            auto distance = airport.second->distanceToPoint(dest.first);

            if (distance < lowest) {
                destination.clear();
                destination.push_back(graph.findAirport(airport.first));
                lowest = distance;
                if (lowest == 0) break; // Avoid further checks if distance is zero
            }
            else if (distance == lowest) destination.push_back(graph.findAirport(airport.first));
        }
    }
    std::cout << origin.front()->getCode()<<std::endl;
    for (auto &airport : graph.getAirports()) {
        airport.second->setVisited(false);
        airport.second->setStopCount(INT_MAX);
    }

    std::queue<std::pair<Airport *, std::vector<Airport *>>> q;

    // Initialize the queue with each origin airport and its corresponding source position.
    for (auto &startAirport : origin) {
        std::vector<Airport *> startRoute = {startAirport};
        q.push({startAirport, startRoute});
        startAirport->setVisited(true);
        startAirport->setStopCount(0);
    }

    std::vector<std::vector<Airport *>> allRoutes;
    int minStops = INT_MAX;

    while (!q.empty())
    {
        auto current = q.front();
        q.pop();
        Airport *currentAirport = current.first;
        std::vector<Airport *> currentRoute = current.second;

        for (auto flight : currentAirport->getFlights())
        {
            if (!flight.getDest()->isVisited() && availableAirlines.find(flight.getAirline()) != availableAirlines.end()) {
                flight.getDest()->setVisited(true);
                flight.getDest()->setStopCount(currentAirport->getStopCount() + 1);
                std::vector<Airport *> newRoute = currentRoute;
                newRoute.push_back(flight.getDest());

                q.push({flight.getDest(), newRoute});

                if (std::find(destination.begin(), destination.end(), flight.getDest()) != destination.end()) {
                    if (flight.getDest()->getStopCount() < minStops) {
                        allRoutes.clear();
                        minStops = flight.getDest()->getStopCount();
                    }

                    if (flight.getDest()->getStopCount() == minStops) {
                        bool validRoute = true;

                        for (size_t i = 0; i < newRoute.size() - 1; ++i) {
                            bool airlineFound = false;
                            for (auto &flightSegment : newRoute[i]->getFlightsTo(newRoute[i + 1])) {
                                auto it = availableAirlines.find(flightSegment);
                                if (it != availableAirlines.end()) {
                                    airlineFound = true;
                                    break;
                                }
                            }
                            if (!airlineFound) {
                                validRoute = false;
                                break;
                            }
                        }

                        if (validRoute) {
                            allRoutes.push_back(newRoute);
                        }
                    }
                }
            }
        }
    }


    if (allRoutes.empty())
    {
        std::cout << "No routes available under this condition." << std::endl;
    }
    else {
        std::cout << "Minimum stops to reach destination: " << minStops << std::endl;
        std::cout << "All routes with minimum stops:" << std::endl;
        for (auto &route : allRoutes) {
            auto routeSize = route.size();
            for (auto i = 0; i < routeSize; ++i) {
                std::cout << route[i]->getName() << "(" << route[i]->getCode() << ")";
                if (i < routeSize - 1)
                {
                    for (auto &flightSegment : route[i]->getFlightsTo(route[i + 1])) {
                        auto it = availableAirlines.find(flightSegment);
                        if (it != availableAirlines.end())
                            std::cout << " [" << it->getCode() << "]";
                    }
                    std::cout << " -> ";
                }
            }
            std::cout << std::endl;
        }
    }
}

/**
 * Function that validates the that it recieves, this means finds out if the city or airport are valid
 * Time Complexity: O(n)
 **/

bool Application::validateData(std::string data) {

    auto it = airlines.find(data);
    if(it != airlines.end()) return true; //found airline by code
    auto it2 = cityMap.find(data);
    if(it2 != cityMap.end()) return true; //found city
    for(auto aiport: airports) //found airport name or code
        if(aiport.getName() == data || aiport.getCode() == data) return true;
    for(auto airline: airlines) //airline by name
        if(airline.second.getName() == data) return true;

    return false;
}

