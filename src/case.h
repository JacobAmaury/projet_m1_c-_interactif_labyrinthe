#ifndef CASE_H
#define CASE_H
#include <vector>
using namespace std;

enum type_Case {MUR, 
                PASSAGE, 
                TRESOR, 
                MONSTRE, 
                PIEGE,
                CHARACTER};

class Case{
    private:
        vector<int> coord_case;
    public:
        Case();
        virtual wchar_t afficher() = 0;
        virtual ~Case();
        vector<int> get_coord_case();
        void set_coord_case(int x, int y);
};


class Mur : public Case{
    public :
        Mur();
        wchar_t afficher();


};
class Passage : public Case{
    public :
        Passage();
        wchar_t afficher();
    };


class Tresor : public Case{
    private:
        int valeur;
    public :
        Tresor(int valeur);
        wchar_t afficher();
};

class Piege : public Case{
    private:
        int degat;
    public :
        Piege(int degat);
        wchar_t afficher();
};

class CaseFactory{
    public :
        static Case* createCase(type_Case t);
};



#endif