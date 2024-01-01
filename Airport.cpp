//
// Created by tiagomonteiro on 12/20/23.
//

#include <complex>
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

int Airport::getStopCount() const {
    return stopCount;
}

void Airport::setStopCount(int stopCount) {
    Airport::stopCount = stopCount;
}

/**
 * Function that calculates the distance from an airport to some coordinates
 * Time Complexity: O(1)
 **/

float Airport::distanceToPoint(std::string point) {
    auto commaPos = point.find(',');
    auto x = point.substr(0, commaPos);
    auto y = point.substr(commaPos + 1);
    auto destLat = std::stof(x);
    auto destLon = std::stof(y);

    // Helper function to convert degrees to radians
    auto toRadians = [](float degrees) {
        return degrees * (M_PI / 180.0);
    };

    // Calculate differences in coordinates
    auto dLat = toRadians(destLat - this->getLat());
    auto dLon = toRadians(destLon - this->getLon());

    // Haversine formula
    auto a = std::sin(dLat / 2) * std::sin(dLat / 2) +
             std::cos(toRadians(this->getLat())) * std::cos(toRadians(destLat)) *
             std::sin(dLon / 2) * std::sin(dLon / 2);
    auto c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    // Calculate distance in kilometers
    const float EarthRadiusKm = 6371.0f; // Earth's radius in kilometers
    return EarthRadiusKm * c;
}

std::vector<Airline> Airport::getFlightsTo(Airport *&pAirport) {

    std::vector<Airline> res;
    for(auto flight: this->getFlights())
        if(flight.getDest() == pAirport)
            res.push_back(flight.getAirline());

    return res;
}
