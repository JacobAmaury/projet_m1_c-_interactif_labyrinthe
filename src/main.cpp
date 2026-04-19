#include <iostream>
#include "donjon.h"
#include "case.h"
// #include "character.h"
using namespace std;





int main(){
    setlocale(LC_ALL, "");// pour les carrées (config terminal pour unicode)
    wcout.imbue(locale("")); // pour les carrés
    Donjon D1(15, 15);
    D1.set_entry(0,0);
    D1.afficher();
    D1.generer_donjon();
    D1.afficher();

    return 0;



    return 0;
}