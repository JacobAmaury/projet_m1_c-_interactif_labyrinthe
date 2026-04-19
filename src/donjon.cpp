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

