//
// Created by tiagomonteiro on 12/20/23.
//

#include <iostream>
#include "Graph.h"

void Graph::addAirport(Airport airport)
{
    vertexSet.push_back(airport);

}

const std::vector<Airport> &Graph::getAirports() const {
    return vertexSet;
}

Graph::Graph() {

};
