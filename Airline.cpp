//
// Created by tiagomonteiro on 12/20/23.
//

#include "Airline.h"

Airline::Airline() = default;

Airline::Airline(std::string code, std::string name, std::string callSign, std::string country) {
    this->code = code;
    this->name = name;
    this->callSign = callSign;
    this->country = country;

}

const std::string &Airline::getCode() const {
    return code;
}

const std::string &Airline::getName() const {
    return name;
}

const std::string &Airline::getCallSign() const {
    return callSign;
}

const std::string &Airline::getCountry() const {
    return country;
}

bool Airline::operator<(const Airline &airline) const {
    return this->code < airline.getCode();
}

