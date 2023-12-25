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
    void getVertex();
    void numberOfAirports();
    void flightsFromAirport(std::string airport);
    void flightsLeavingPerCity();
    void flightsArrivingPerCity();
    void flightsPerAirline();
    void reachableDestinations( std::string airport,int n);
    void maximumTrip();

private:
    std::set<Airport> airports;
    std::unordered_map<std::string ,Airline> airlines;
    Graph graph;

};


#endif //AED2324_PRJ2_G04_APPLICATION_H
