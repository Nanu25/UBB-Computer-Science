//
// Created by alex_ on 4/23/2024.
//

#include "Block.h"

Block::Block(int year, int totap, int ocap) : Building(year){
    this->totalApartments = totap;
    this->occupiedAppartament = ocap;
}

bool Block::mustBeRestored() {
    return 2024 - this->constructionYear > 40 && (this->occupiedAppartament * 100 > this->totalApartments * 80);
}

bool Block::canBeDemolished() {
    return (this->occupiedAppartament * 100 < 5 * this->totalApartments);
}

std::string Block::toString() {
    std::string s = "Block Building Construction year " + std::to_string(this->constructionYear) + " total apartaments: " + std::to_string(this->totalApartments) + " occupied appartaments: " + std::to_string(this->occupiedAppartament);
    return s;
}
