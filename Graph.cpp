//
// Created by tiagomonteiro on 12/20/23.
//

#include <iostream>
#include <queue>
#include "Graph.h"

Graph::Graph() {}

void Graph::addAirport(Airport airport){

    auto it = airports.find(airport.getCode());

    if(it == airports.end())
    {
        airports[airport.getCode()] = new Airport(airport);
    }

}

Airport* Graph::findAirport(std::string code)
{
    auto it = airports.find(code);
    if(it == airports.end()) return nullptr;
    return it->second;
}


bool Graph::addFlight(Airport* source, Airport* dest, Airline airline) {

    auto sourceIt = airports.find(source->getCode());
    auto destIt = airports.find(dest->getCode());
    if(sourceIt == airports.end() || destIt == airports.end()) return false;
    auto sourceAirport = sourceIt->second;
    Flight flight (destIt->second,airline);
    sourceAirport->addFlight(flight);
    return true;

}

const std::unordered_map<std::string, Airport *> &Graph::getAirports() const {
    return airports;
}

std::vector<Airport *> Graph::bfs(Airport* source) {
    std::vector<Airport*> res;
    std::queue<Airport*> q;

    for (auto anAirport : this->getAirports()) anAirport.second->setVisited(false);
    source->setVisited(true);

    q.push(source);
    while (!q.empty()) {
        auto currentAirport = q.front();
        q.pop();
        for (auto flight : currentAirport->getFlights())
        {
            if (!flight.getDest()->isVisited())
            {
                flight.getDest()->setVisited(true);
                q.push(flight.getDest());
                res.push_back(flight.getDest());
            }
        }
    }

    return res;
}
