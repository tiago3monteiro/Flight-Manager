//
// Created by tiagomonteiro on 12/20/23.
//

#include "Flight.h"

Flight::Flight(Airport dest, Airline airline)
{
    this->dest = new Airport(dest);
    this->airline = airline;

}

Airport *Flight::getDest() const {
    return dest;
}

const Airline &Flight::getAirline() const {
    return airline;
}
