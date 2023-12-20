//
// Created by tiagomonteiro on 12/20/23.
//

#ifndef AED2324_PRJ2_G04_AIRPORT_H
#define AED2324_PRJ2_G04_AIRPORT_H


#include <string>
#include <vector>
#include "Flight.h"

class Flight;

class Airport {

public:
    Airport();

    Airport(std::string code, std::string name, std::string city,std::string country,float lat,float lon);//info
    const std::string &getCode() const;
    const std::string &getName() const;
    const std::string &getCity() const;
    const std::string &getCountry() const;
    float getLat() const;
    float getLon() const;
    const std::vector<Flight> &getFlights() const; //edges

    bool operator< (const Airport& airport) const;
    void addFlight(Flight flight); //add edges


private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    std::vector<Flight> flights;
    float lat;
    float lon;

};


#endif //AED2324_PRJ2_G04_AIRPORT_H