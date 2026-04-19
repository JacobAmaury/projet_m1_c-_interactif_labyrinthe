#include <iostream>
#include <vector>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <locale> //pour les carrées
#include <typeinfo>
#include "case.h"
#include "donjon.h"
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
}

void Donjon::set_entry(int x, int y){
    x_entry = x;
    y_entry = y;
    grille[x][y] = CaseFactory().createCase(PASSAGE);
}

bool Donjon::is_entry(int x, int y){
    if((x == x_entry) and (y == y_entry)){return true;}
    return false;
}

bool Donjon::is_exit(int x, int y){
    if((x == x_exit) and (y == y_exit)){return true;}
    return false;
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
    if(r<5){
        grille[x][y] = CaseFactory().createCase(TRESOR);
    }
    //Ajout monstre
    else if (r<13)
    {
        grille[x][y] = CaseFactory().createCase(PIEGE);
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
    wcout<<"test"<<endl;
    if(typeid(*grille[x][y])==typeid(Mur)){
        int dist_min, dist;
        dist_min = 1000;

        for(int i=0; i<chemin.size();i++){
            dist = (abs(chemin[i][0]-x)+abs(chemin[i][1]-y));
            if(dist<dist_min){
                wcout<<"dist ="<<dist<<"x="<<chemin[i][0]<<"y="<<chemin[i][1]<<endl;
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
    wcout<<"x_exit="<<x_exit<<"y_exit="<<y_exit<<endl;
}

int Donjon::trouver_chemin(int player_x, int player_y){
    vector<vector<bool>> visite(h, vector<bool>(l,false));
    vector<vector<vector<int>>> parent(h, vector<vector<int>>(l, vector<int>(2,0)));
    vector<vector<int>> file;
    vector<int> current;
    vector<int> voisin;

    file.push_back({player_x, player_y});
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

int Donjon::recons_chemin(vector<vector<vector<int>>> parent, int player_x, int player_y){
    int cpt = 0;
    vector<int> current = {x_exit, y_exit};

    while (!is_entry(current[0], current[1]))
    {
        current = parent[current[0]][current[1]];
        cpt++;
    }
    return cpt;
}


bool Donjon::in_grid(int x, int y){
    if((x<0 or x>=l) or (y<0 or y>=h)){return false;}
    return true;
}
