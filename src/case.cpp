#include <iostream>
#include <vector>
#include "case.h"
#include "character.h"
using namespace std;



#define VALEUR 10
#define DEGAT 10 



Case::Case(){};

Case::~Case() = default;

vector<int> Case::get_coord_case(){return coord_case;}

void Case::set_coord_case(int x, int y){
    coord_case[0] = x;
    coord_case[1] = y;
}

Mur::Mur(){};
wchar_t Mur::afficher(){
    return U'\u25AE';
}



Passage::Passage():Case(){};
wchar_t Passage::afficher(){
    return ' ';
}

Tresor::Tresor(int valeur):Case(){this->valeur=valeur;};
wchar_t Tresor::afficher(){
    return '+';
}

Piege::Piege(int degat):Case(){this->degat=degat;};
wchar_t Piege::afficher(){
    return 'T';
}

Monstre::Monstre(int pv):Case(){this->pv = pv;};
wchar_t Monstre::afficher(){
    return 'M';
}

void Monstre::damage(int amount){
    pv -= amount;
    if(pv < 0) pv = 0;
}

int Monstre::get_pv() const {
    return pv;
}

bool Monstre::is_dead() const {
    return pv <= 0;
}

Case* CaseFactory::createCase(type_Case t){
    switch (t)
    {
    case MUR:
        return new Mur();
    case PASSAGE:
        return new Passage();
    case TRESOR:
        return new Tresor(VALEUR);
    case MONSTRE:
        return new Monstre();
    case PIEGE:
        return new Piege(DEGAT);
    case CHARACTER:
        return new Character("Maelle");
    }
    return nullptr;
};
