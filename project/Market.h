#include "Living.h"

class marketClass{
private:
    int maxItems;                       //items in market
    Item **items;

    int maxSpells;                      //spells in market
    Spell **spells;
public:
    marketClass();
    ~marketClass()
    {
        for(int i=0; i<maxItems; i++)   //delete items
            if(items[i] != NULL)
                delete items[i];
        delete[] items;

        for(int i=0; i<maxSpells; i++)  //delete spells
            if(spells[i] != NULL)
                delete spells[i];
        delete[] spells;
    }

    bool buy (char choice, int number, Hero& hero);
    bool sell(char choice, int number, Hero& hero);
    void show();
};
