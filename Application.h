//
// Created by tiagomonteiro on 12/20/23.
//

#ifndef AED2324_PRJ2_G04_APPLICATION_H
#define AED2324_PRJ2_G04_APPLICATION_H


#include <set>
#include <queue>
#include <unordered_map>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

class Application {

public:
    Application();
    void globalStatistics(int key);
    void flightsFromAirport(std::string airport);
    void flightsLeavingPerCity(std::string cityName);
    void flightsArrivingPerCity(std::string City);
    void flightsPerAirline(std::string airlineName);
    void reachableDestinations( std::string airport,int n);
    void greatestAirtraffic(int k);
    void maximumTrip();
    std::pair<std::vector<Airport*>,int> max_distance_bfs(Airport* source);
    void essencialAirports();
    void bestFlightOption(std::pair<std::string ,int>source, std::pair<std::string ,int>dest);
    void bestFlightOptionAirline(std::pair<std::string ,int>source, std::pair<std::string ,int>dest, std::vector<std::string> airlines);
    bool validateData(std::string data);

private:
    std::set<Airport> airports;
    std::unordered_map<std::string ,Airline> airlines;
    Graph graph;
    std::unordered_map<std::string,std::vector<std::string>> cityMap;

};


#endif //AED2324_PRJ2_G04_APPLICATION_H
