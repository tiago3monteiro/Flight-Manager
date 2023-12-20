//
// Created by tiagomonteiro on 12/20/23.
//
#ifndef AED2324_PRJ2_G04_FLIGHT_H
#define AED2324_PRJ2_G04_FLIGHT_H

#include <string>
#include "Airport.h"
#include "Airline.h"

class Airport;
class Airline;

class Flight {

public:
    Flight(Airport dest, Airline airline);

    Airport *getDest() const;

    const Airline &getAirline() const;

private:
    Airport* dest;
    Airline airline;

};

#endif //AED2324_PRJ2_G04_FLIGHT_H
