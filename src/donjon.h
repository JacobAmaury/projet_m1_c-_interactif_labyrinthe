#ifndef DONJON_H
#define DONJON_H
#include <vector>
#include "case.h"
#include "character.h"
using namespace std;


class Donjon{
    private: 
        vector<vector<Case*>> grille;
        vector<vector<int>> chemin;
        vector<int> player_coord;

        int l, h;
        int x_entry, y_entry;;
        int x_exit, y_exit;

        bool combat_monstre(int prev_x, int prev_y, int mon_x, int mon_y);
        void afficher_stats() const;
        vector<char> possible_moves() const;
        Character* get_player() const;

    public:
        Donjon(int l, int h);
        void afficher();
        void set_entry(int x, int y);
        void set_exit(int x, int y);
        bool is_entry(int x, int y) const;
        bool is_exit(int x, int y) const;
        bool in_grid(int x, int y) const;
        void recur_back_track(int x, int y, int index, bool forward);
        void placer_element(int x, int y);
        void generer_donjon();
        bool move_player(char command);
        bool player_at_exit() const;

        
        int trouver_chemin(int player_x, int player_y) const;
        int recons_chemin(vector<vector<vector<int>>> parent, int player_x, int player_y) const;
        
    
};

#endif