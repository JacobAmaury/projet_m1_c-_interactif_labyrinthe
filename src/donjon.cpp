#include <iostream>
#include <vector>
using namespace std;

enum type_Case {MUR, PASSAGE, TRESOR, MONSTRE, PIEGE};

class Case{
    public:
        Case(){};
        virtual char afficher() = 0;
        virtual ~Case() = default;
};

class Mur : public Case{
    public :
        Mur():Case(){};
        char afficher() override{
            return '#';
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
        Mur m;
    public:
        Donjon(int l, int h){
            this->l = l;
            this->h = h;
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
    
};


int main(){

    Donjon D1(15, 15);
    D1.afficher();

    return 0;
}