#include <iostream>
#include <vector>
#include "case.h"
#include "character.h"
using namespace std;


Character::Character(string name){
    this->name = name;
    this->pv = 100;
}

wchar_t Character::afficher(){
    return '%';
}

void Character::add_tres(){
    inventory[0] += 1;
}

void Character::set_pv(int add, int set){
    if(add != 0){
        pv = set;
    }
    else{
        pv += add;
    }
}

bool Character::is_dead(){
    if(pv <= 0){
        return true;
    }
    else{return false;}
}
