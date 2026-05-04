#ifndef CHARACTER_H
#define CHARACTER_H
#include <vector>
#include <string>
#include "case.h"
#include <iostream>
using namespace std;




class Character: public Case{
    private:
        int pv;
        int tresors;
    public:
        string name;
        Character(string name);
        wchar_t afficher() override;
        void add_tres();
        bool use_tresor();
        int get_tresors() const;
        int get_pv() const;
        void heal(int amount);
        void damage(int amount);
        bool is_dead() const;
};




#endif 