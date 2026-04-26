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
        vector<int> inventory;  
    public:

        string name;
        Character(string name);
        wchar_t afficher();
        void add_tres();
        void set_pv(int add, int set);
        bool is_dead();
};




#endif 