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
    D1.generer_donjon();
    D1.set_entry(0,0);
    D1.set_exit(14,14);

    wcout << "Il faut: " << D1.trouver_chemin(0,0) << " cases avant la fin" << endl;

    char commande;
    while(!D1.player_at_exit()){
        D1.afficher();
        wcout << "Deplacement: z=haut, s=bas, q=gauche, d=droite, x=quitter" << endl;
        cin >> commande;
        if(commande == 'x'){
            wcout << "Sortie annulee." << endl;
            break;
        }

        if(!D1.move_player(commande)){
            wcout << "Deplacement impossible." << endl;
        }
    }

    if(D1.player_at_exit()){
        D1.afficher();
        wcout << "Bravo, vous avez atteint la sortie !" << endl;
    }

    return 0;
}