#include <iostream>
#include <vector>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <locale> //pour les carrées
#include <typeinfo>
#include "case.h"
#include "donjon.h"
#include "character.h"
using namespace std;


Donjon::Donjon(int l, int h){
    this->l = l;
    this->h = h;
    chemin.resize(h*l, vector<int>(2));

    grille.resize(h);
    for(int i=0; i<h; i++){
        grille[i].resize(l);
        for(int j=0; j<l; j++){
            grille[i][j] = CaseFactory().createCase(MUR);
        }
    }
} 

void Donjon::afficher(){
    for(int i=0; i<h; i++){
        for(int j=0; j<l; j++){
            wcout<<grille[i][j]->afficher();
        }
        wcout << endl;
    }
    wcout << endl;
    afficher_stats();
}

Character* Donjon::get_player() const {
    if(player_coord.size() != 2) return nullptr;
    return dynamic_cast<Character*>(grille[player_coord[0]][player_coord[1]]);
}

void Donjon::afficher_stats() const {
    Character* player = get_player();
    if(player == nullptr) return;
    int distance = trouver_chemin(player_coord[0], player_coord[1]);
    wcout << L"Position : (" << player_coord[0] << L", " << player_coord[1] << L")" << endl;
    wcout << L"Sante : " << player->get_pv() << L"/100" << endl;
    wcout << L"Inventaire : " << player->get_tresors() << L" tresors" << endl;
    wcout << L"Distance a la sortie : " << distance << L" cases" << endl;
    vector<char> moves = possible_moves();
    wcout << L"Mouvements possibles : ";
    if(moves.empty()){
        wcout << L"Aucun";
    } else {
        for(size_t i=0; i<moves.size(); i++){
            if(i) wcout << L" ";
            wcout << moves[i];
        }
    }
    wcout << endl << endl;
}

void Donjon::set_entry(int x, int y){
    x_entry = x;
    y_entry = y;
    player_coord = {x,y};

    grille[x][y] = CaseFactory().createCase(CHARACTER);

}

bool Donjon::is_entry(int x, int y) const {
    return x == x_entry && y == y_entry;
}

bool Donjon::is_exit(int x, int y) const {
    return x == x_exit && y == y_exit;
}

void Donjon::recur_back_track(int x, int y, int index, bool forward){
    if(is_entry(x,y) and !forward){return;}

    // this->afficher();
    enum direction {NORD=0,
                    SUD,
                    EST,
                    OUEST};
    
    chemin[index][0] = x;
    chemin[index][1] = y;

    
    int ny, nx;
    int iy, ix;
    bool is_ok = true;

    vector<int> directions = {0, 1, 2, 3};

    random_device rd; // voir https://www.geeksforgeeks.org/cpp/how-to-shuffle-a-vector-in-cpp/
    mt19937 g(rd());

    shuffle(directions.begin(), directions.end(), g);
    

    for(int dir=0; dir<4; dir++){
        switch (directions[dir]){
        case NORD:
            ny = y-2;
            nx = x;
            iy = y-1;
            ix = x;
            break;
        case SUD:
            ny = y+2;
            nx = x;
            iy = y+1;
            ix = x;
            break;
        case EST:
            ny = y;
            nx = x+2;
            iy = y;
            ix = x+1;
            break;
        case OUEST:
            ny = y;
            nx = x-2;
            iy = y;
            ix = x-1;
            break;
        }
        if((ny >= h) or (ny < 0) or (nx >= l) or (nx < 0)){
            is_ok = false;
        }   
        else
        {
            if(typeid(*grille[nx][ny]) == typeid(Mur)){
                grille[ix][iy] = CaseFactory().createCase(PASSAGE);
                grille[nx][ny] = CaseFactory().createCase(PASSAGE);
                recur_back_track(nx, ny, ++index, forward);
            }
            else{
                is_ok = false;
            }
        }
    }         
    if(not(is_ok)){
        if(index == 0){return;}
        recur_back_track(chemin[index-1][0], chemin[index-1][1], index-1, not(forward));
    }
}

void Donjon::placer_element(int x, int y){
    int r = rand() % 101;
    if(r < 5){
        grille[x][y] = CaseFactory().createCase(TRESOR);
    }
    else if(r < 13){
        grille[x][y] = CaseFactory().createCase(PIEGE);
    }
    else if(r < 20){
        grille[x][y] = CaseFactory().createCase(MONSTRE);
    }
}

void Donjon::generer_donjon(){
    this->recur_back_track(0,0,0,true);

    int x,y;
    int chemin_length = chemin.size();

    for(int i=0; i<chemin_length; i++){
        x = chemin[i][0];
        y = chemin[i][1];
        placer_element(x,y);
    }
}

void Donjon::set_exit(int x, int y){
    if(typeid(*grille[x][y])==typeid(Mur)){
        int dist_min = 1000;
        int dist;

        for(int i=0; i<chemin.size();i++){
            dist = abs(chemin[i][0]-x) + abs(chemin[i][1]-y);
            if(dist < dist_min){
                dist_min = dist;
                x_exit = chemin[i][0];
                y_exit = chemin[i][1];
            }
        }
    }
    else{
        x_exit = x;
        y_exit = y;
    }
}

int Donjon::trouver_chemin(int player_x, int player_y) const {
    vector<vector<bool>> visite(h, vector<bool>(l,false));
    vector<vector<vector<int>>> parent(h, vector<vector<int>>(l, vector<int>(2,0)));
    vector<vector<int>> file;
    vector<int> current;
    vector<int> voisin;

    file.push_back({player_x, player_y});
    visite[player_x][player_y] = true;
    while(file.size()!=0){
        
        current = file[0];
        file.erase(file.begin());
        if(is_exit(current[0], current[1])){
            return recons_chemin(parent, player_x, player_y);
        }

        for(int i=0; i<4; i++){
            switch (i)
            {
            case 0:
                voisin = {current[0], current[1]-1};
                break;
            case 1:
                voisin = {current[0], current[1]+1};
                break;
            case 2:
                voisin = {current[0]-1, current[1]};
                break;
            case 3:
                voisin = {current[0]+1, current[1]};
                break;
            }
            if(in_grid(voisin[0], voisin[1])){
                if (!visite[voisin[0]][voisin[1]]){
                    if(typeid(*grille[voisin[0]][voisin[1]])!=typeid(Mur)){
                        
                        visite[voisin[0]][voisin[1]]=true;
                        parent[voisin[0]][voisin[1]][0] = current[0];
                        parent[voisin[0]][voisin[1]][1] = current[1];
                        file.push_back(voisin);
                    }
                }
            }
        }
    }
    return -1;

}

int Donjon::recons_chemin(vector<vector<vector<int>>> parent, int player_x, int player_y) const {
    int cpt = 0;
    vector<int> current = {x_exit, y_exit};

    while (!(current[0] == player_x && current[1] == player_y))
    {
        current = parent[current[0]][current[1]];
        cpt++;
    }
    return cpt;
}


bool Donjon::move_player(char command){
    int dx = 0;
    int dy = 0;

    switch(command){
        case 'w':
        case 'W':
            dx = -1;
            break;
        case 's':
        case 'S':
            dx = 1;
            break;
        case 'a':
        case 'A':
            dy = -1;
            break;
        case 'd':
        case 'D':
            dy = 1;
            break;
        default:
            return false;
    }

    int nx = player_coord[0] + dx;
    int ny = player_coord[1] + dy;

    if(!in_grid(nx, ny) || typeid(*grille[nx][ny]) == typeid(Mur)){
        return false;
    }

    Character* player = get_player();
    if(player == nullptr) return false;

    Case* next_case = grille[nx][ny];
    if(typeid(*next_case) == typeid(Tresor)){
        player->add_tres();
        wcout << L"Vous ramassez un tresor ! Inventaire: " << player->get_tresors() << L" tresors." << endl;
        grille[nx][ny] = CaseFactory().createCase(PASSAGE);
    }
    else if(typeid(*next_case) == typeid(Piege)){
        player->damage(2);
        wcout << L"Vous activez un piege et perdez 2 points de vie." << endl;
        grille[nx][ny] = CaseFactory().createCase(PASSAGE);
    }
    else if(typeid(*next_case) == typeid(Monstre)){
        if(!combat_monstre(player_coord[0], player_coord[1], nx, ny)){
            return false;
        }
        grille[nx][ny] = CaseFactory().createCase(PASSAGE);
    }

    grille[player_coord[0]][player_coord[1]] = CaseFactory().createCase(PASSAGE);
    grille[nx][ny] = player;
    player_coord = {nx, ny};

    return true;
}

bool Donjon::combat_monstre(int prev_x, int prev_y, int mon_x, int mon_y){
    Character* player = get_player();
    Monstre* monster = dynamic_cast<Monstre*>(grille[mon_x][mon_y]);
    if(player == nullptr || monster == nullptr) return false;

    wcout << L"\n=== Rencontre avec un monstre ! ===" << endl;
    while(true){
        wcout << L"Monstre PV: " << monster->get_pv() << L" | Votre PV: " << player->get_pv() << L" | Tresors: " << player->get_tresors() << endl;
        wcout << L"Choix: 1) fuir  2) combattre  3) consommer un tresor (+3 PV)" << endl;
        int choix;
        cin >> choix;

        if(choix == 1){
            wcout << L"Vous prenez la fuite et retournez en arriere." << endl;
            return false;
        }
        else if(choix == 3){
            if(player->use_tresor()){
                wcout << L"Vous consommez un tresor et gagnez 3 PV." << endl;
            }
            else {
                wcout << L"Vous n'avez pas de tresors a consommer." << endl;
            }
            continue;
        }
        else if(choix == 2){
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dice(1, 6);
            int damage = dice(gen);
            monster->damage(damage);
            wcout << L"Vous infligez " << damage << L" points de degats." << endl;
            if(monster->is_dead()){
                wcout << L"Le monstre est vaincu !" << endl;
                return true;
            }
            int monster_attack = dice(gen);
            player->damage(monster_attack);
            wcout << L"Le monstre riposte et vous inflige " << monster_attack << L" points." << endl;
            if(player->is_dead()){
                wcout << L"Vous etes mort... fin de la partie." << endl;
                exit(0);
            }
        }
        else {
            wcout << L"Choix invalide." << endl;
        }
    }
}

vector<char> Donjon::possible_moves() const {
    vector<char> moves;
    int x = player_coord[0];
    int y = player_coord[1];
    if(in_grid(x-1, y) && typeid(*grille[x-1][y]) != typeid(Mur)) moves.push_back(L'w');
    if(in_grid(x+1, y) && typeid(*grille[x+1][y]) != typeid(Mur)) moves.push_back(L's');
    if(in_grid(x, y-1) && typeid(*grille[x][y-1]) != typeid(Mur)) moves.push_back(L'a');
    if(in_grid(x, y+1) && typeid(*grille[x][y+1]) != typeid(Mur)) moves.push_back(L'd');
    return moves;
}

bool Donjon::player_at_exit() const {
    return is_exit(player_coord[0], player_coord[1]);
}

bool Donjon::in_grid(int x, int y) const {
    return !((x<0 || x>=l) || (y<0 || y>=h));
}
