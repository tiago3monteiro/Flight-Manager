//
// Created by tiagomonteiro on 12/20/23.
//

#ifndef AED2324_PRJ2_G04_GRAPH_H
#define AED2324_PRJ2_G04_GRAPH_H


#include <vector>
#include "Airport.h"

class Graph {
public:
    Graph();
    void addAirport(Airport airport);

    const std::vector<Airport> &getAirports() const;

private:
    std::vector<Airport> vertexSet;      // vertex set

};


#endif //AED2324_PRJ2_G04_GRAPH_H
