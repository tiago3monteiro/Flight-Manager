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

bool Airport::operator==(const Airport &airport) const {
    return airport.getCode() == this->getCode();
}

bool Airport::isVisited() const {
    return visited;
}

void Airport::setVisited(bool visited) {
    Airport::visited = visited;
}

int Airport::getNum() const {
    return num;
}

void Airport::setNum(int num) {
    Airport::num = num;
}

int Airport::getLow() const {
    return low;
}

void Airport::setLow(int low) {
    Airport::low = low;
}

int Airport::getInbound() const {
    return inbound;
}

void Airport::setInbound(int inbound) {
    Airport::inbound = inbound;
}

int Airport::getOutbound() const {
    return outbound;
}

void Airport::setOutbound(int outbound) {
    Airport::outbound = outbound;
}

bool Airport::isProcessed() const {
    return processed;
}

void Airport::setProcessed(bool processed) {
    this->processed = processed;
}

