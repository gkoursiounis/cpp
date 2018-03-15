#include <string>

using namespace std;

class Spell{                            //abstract base class
private:
    string name;
    int price;
    int minLevel;
    int damageRange;
    int energyRequired;
    int rounds;                         //number of rounds the spell has power
public:
    Spell(string name_, int price_, int minLevel_, int damage_, int energy_, int rounds_):
        name(name_), price(price_), minLevel(minLevel_), damageRange(damage_), energyRequired(energy_), rounds(rounds_) {}
    virtual ~Spell() {}

    virtual void getInfo()
    {
        cout << "Name:" << name << endl << "Price: " << price << endl << "Minimum level: "
             << minLevel << endl << "Damage range: " << damageRange << endl
             << "Energy required: " << energyRequired << endl;
    }

    int getMoney()          { return price; }
    int getMinLevel()       { return minLevel; }
    int getEnergyRequired() { return energyRequired; }
    int getDamageRange()    { return damageRange; }
    int getRounds()         { return rounds; }

    virtual char whatSpellIs() = 0;     //returns a character which indicates the type of spell (pure virtual)
};


class IceSpell : public Spell{
public:
    IceSpell(string name_, int price_, int minLevel_, int damage_, int energy_, int rounds_):
        Spell(name_, price_, minLevel_, damage_, energy_, rounds_) {}

    char whatSpellIs() { return 'i'; }
};


class FireSpell : public Spell{
public:
    FireSpell(string name_, int price_, int minLevel_, int damage_, int energy_, int rounds_):
        Spell(name_, price_, minLevel_, damage_, energy_, rounds_) {}

    char whatSpellIs() { return 'f'; }
};


class LightingSpell : public Spell{
public:
    LightingSpell(string name_, int price_, int minLevel_, int damage_, int energy_, int rounds_):
        Spell(name_, price_, minLevel_, damage_, energy_, rounds_) {}

    char whatSpellIs() { return 'l'; }
};
