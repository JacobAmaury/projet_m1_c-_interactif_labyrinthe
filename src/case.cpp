#include <iostream>
#include <vector>
#include "case.h"
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

Case* CaseFactory::createCase(type_Case t){
    switch (t)
    {
    case MUR:
        return new Mur();
        break;
    case PASSAGE:
        return new Passage();
        break;
    case TRESOR:
        return new Tresor(VALEUR);
        break;
    case MONSTRE:
        break;
    case PIEGE:
        return new Piege(DEGAT);
        break;
    }
    return nullptr;
};
