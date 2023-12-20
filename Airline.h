//
// Created by tiagomonteiro on 12/20/23.
//

#ifndef AED2324_PRJ2_G04_AIRLINE_H
#define AED2324_PRJ2_G04_AIRLINE_H


#include <string>

class Airline {

public:
    Airline();
    Airline(std::string code,std::string name,std::string callSign,std::string country);
    bool operator< (const Airline& airline) const;

    const std::string &getCode() const;

    const std::string &getName() const;

    const std::string &getCallSign() const;

    const std::string &getCountry() const;

private:
    std::string code;
    std::string name;
    std::string callSign;
    std::string country;

};



#endif //AED2324_PRJ2_G04_AIRLINE_H
