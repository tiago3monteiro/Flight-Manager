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
    bool operator== (const Airport& airport) const;
    void addFlight(Flight flight); //add edges
    bool isVisited() const;
    void setVisited(bool visited);
    int getNum() const;
    void setNum(int num);
    int getLow() const;
    void setLow(int low);
    int getInbound() const;
    void setInbound(int inbound);
    int getOutbound() const;
    void setOutbound(int outbound);
    void setProcessed(bool processed);
    bool isProcessed() const;

private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    std::vector<Flight> flights;
    float lat;
    float lon;
    bool visited;
    bool processed;
    int num;
    int low;
    int inbound;
    int outbound;

};


#endif //AED2324_PRJ2_G04_AIRPORT_H
