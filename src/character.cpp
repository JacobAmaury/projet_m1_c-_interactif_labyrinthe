#include <iostream>
#include <vector>
#include "case.h"
#include "character.h"
using namespace std;


Character::Character(string name){
    this->name = name;
    this->pv = 40;
    this->tresors = 0;
}

wchar_t Character::afficher(){
    return '%';
}

void Character::add_tres(){
    tresors += 1;
}

bool Character::use_tresor(){
    if(tresors <= 0){
        return false;
    }
    tresors -= 1;
    heal(3);
    return true;
}

int Character::get_tresors() const {
    return tresors;
}

int Character::get_pv() const {
    return pv;
}

void Character::heal(int amount){
    pv += amount;
    if(pv > 100) pv = 100;
}

void Character::damage(int amount){
    pv -= amount;
    if(pv < 0) pv = 0;
}

bool Character::is_dead() const {
    return pv <= 0;
}
