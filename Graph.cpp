//
// Created by tiagomonteiro on 12/20/23.
//

#include <iostream>
#include "Graph.h"

Graph::Graph() {}

void Graph::addAirport(Airport airport){

    airportsSet.insert(new Airport(airport));
}

Airport* Graph::findAirport(std::string code)
{
    for(auto airport: airportsSet)
    {
        if(airport->getCode() == code || airport->getName() == code)
            return airport;
    }
    return nullptr;
}


bool Graph::addFlight(Airport* source, Airport* dest, Airline airline) {


    for(auto airport: airportsSet)
    {
        if(airport->getName() == source->getName())
        {
            Flight flight(dest,airline);
            airport->addFlight(flight);
            return true;
        }
    }
    return false;
}

const std::set<Airport *> &Graph::getAirportsSet() const {
    return airportsSet;
};
