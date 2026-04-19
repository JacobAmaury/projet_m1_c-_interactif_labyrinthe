#ifndef DONJON_H
#define DONJON_H
#include <vector>
#include "case.h"
using namespace std;


class Donjon{
    private: 
        vector<vector<Case*>> grille;
        vector<vector<int>> chemin;

        int l, h;
        int x_entry, y_entry;;
        int x_exit, y_exit;

    public:
        Donjon(int l, int h);
        void afficher();
        void set_entry(int x, int y);
        void set_exit(int x, int y);
        bool is_entry(int x, int y);
        bool is_exit(int x, int y);
        bool in_grid(int x, int y);
        void recur_back_track(int x, int y, int index, bool forward);
        void placer_element(int x, int y);
        void generer_donjon();
        
        int trouver_chemin(int player_x, int player_y);
        int recons_chemin(vector<vector<vector<int>>> parent, int player_x, int player_y);
        
    
};

#endif