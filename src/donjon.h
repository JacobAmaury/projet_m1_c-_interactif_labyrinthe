#ifndef DONJON_H
#define DONJON_H
#include <vector>
#include "case.h"
using namespace std;


class Donjon{
    private: 
        vector<vector<Case*>> grille;
        vector<vector<int>> chemin;

        int l;
        int h;
        int x_entry;
        int y_entry;
        int x_exit;
        int y_exit;

    public:
        Donjon(int l, int h);
        void afficher();
        void set_entry(int x, int y);
        bool is_entry(int x, int y);
        void recur_back_track(int x, int y, int index, bool forward);
        void placer_element(int x, int y);
        void generer_donjon();
    
};

#endif