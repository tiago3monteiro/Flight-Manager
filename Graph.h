//
// Created by tiagomonteiro on 12/20/23.
//

#ifndef AED2324_PRJ2_G04_GRAPH_H
#define AED2324_PRJ2_G04_GRAPH_H


#include <vector>
#include <set>
#include "Airport.h"

class Graph {
public:
    Graph();
    void addAirport(Airport airport);
    Airport* findAirport(std::string code);
    bool addFlight(Airport* source, Airport* dest ,Airline airline);
    const std::set<Airport *> &getAirportsSet() const;

private:
    std::set<Airport*> airportsSet; // vertex set

};


#endif //AED2324_PRJ2_G04_GRAPH_H
