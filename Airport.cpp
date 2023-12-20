//
// Created by tiagomonteiro on 12/20/23.
//

#include "Airport.h"

Airport::Airport() = default;

Airport::Airport(std::string code, std::string name, std::string city, std::string country, float lat, float lon) {

    this->code = code;
    this-> name = name;
    this->city = city;
    this->country = country;
    this->lat = lat;
    this->lon = lon;
}

const std::string &Airport::getCode() const {
    return code;
}

const std::string &Airport::getName() const {
    return name;
}

const std::string &Airport::getCity() const {
    return city;
}

const std::string &Airport::getCountry() const {
    return country;
}

float Airport::getLat() const {
    return lat;
}

float Airport::getLon() const {
    return lon;
}

bool Airport::operator<(const Airport &airport) const {
    return this->getCode() < airport.getCode();
}

const std::vector<Flight> &Airport::getFlights() const {
    return flights;
}

void Airport::addFlight(Flight flight){
    flights.push_back(flight);

}


