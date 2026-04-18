#include <iostream>
#include <vector>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <typeinfo>
using namespace std;


enum type_Case {MUR, 
                PASSAGE, 
                TRESOR, 
                MONSTRE, 
                PIEGE};

class Case{
    private:
        vector<int> coord_case = {0,0};
    public:
        Case(){};
        virtual char afficher() = 0;
        virtual ~Case() = default;

        vector<int> get_coord_case(){return coord_case;}
        void set_coord_case(int x, int y){
            coord_case[0] = x;
            coord_case[1] = y;
        }
};

class Mur : public Case{
    public :
        Mur():Case(){};
        char afficher() override{
            return '#';
        }


};
class Passage : public Case{
    public :
        Passage():Case(){};
        char afficher() override{
            return ' ';
        }


};

class CaseFactory{
    public :
        static Case* createCase(type_Case t){
            switch (t)
            {
            case MUR:
                return new Mur();
                break;
            case PASSAGE:
                return new Passage();
                break;
            case TRESOR:
                break;
            case MONSTRE:
                break;
            case PIEGE:
                break;
            }
            return nullptr;
        };

};

class Donjon{
    private: 
        vector<vector<Case*>> grille;
        int l;
        int h;

        int x_entry;
        int y_entry;
        int x_exit;
        int y_exit;
        vector<vector<int>> chemin;
    public:
        Donjon(int l, int h){
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

        void afficher(){
            for(int i=0; i<h; i++){
                for(int j=0; j<l; j++){
                    cout<<grille[i][j]->afficher();
                }
                cout << endl;
            }
            cout << endl;
        }

        void set_entry(int x, int y){
            x_entry = x;
            y_entry = y;
            grille[x][y] = CaseFactory().createCase(PASSAGE);
        }

        bool is_entry(int x, int y){
            if((x == x_entry) and (y == y_entry)){return true;}
            return false;
        }

        void recur_back_track(int x, int y, int index, bool forward){
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
            else{
                return;
            }
        }
    
};


int main(){

    Donjon D1(15, 15);
    D1.set_entry(0,0);
    D1.afficher();
    D1.recur_back_track(0,0,0,true);
    D1.afficher();

    return 0;
}