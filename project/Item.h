#include <iostream>
#include <string>

using namespace std;

class Hero;

class Item{     //abstract base class
private:
    string name;
    int price;
    int minLevel;
public:
    Item(string name_, int price_, int minLevel_): name(name_), price(price_), minLevel(minLevel_) {}
	virtual ~Item() {}

	int getMoney()    { return price; }
	int getMinLevel() { return minLevel; }

    virtual void getDamages(int &) {}
    virtual void getHands(int &)   {}
    virtual void getType(string&)  {}

    virtual void getInfo()
    {
        cout << "Name: " << name <<  endl << "Price: " << price << endl
             << "Minimum level for use: " << minLevel << endl;
    }


    virtual int whatIs() = 0;   //pure virtual..returns 0 if weapon, 1 for armor, 2 for potion
};



class Weapon: public Item{
private:
    int damage;
    int handsRequired;          //1 for one hand, 2 for two hands
public:
    Weapon(int damage_, int hands_, string name_, int price_, int minLevel_): Item(name_, price_, minLevel_)
    {
        damage = damage_;
        handsRequired = hands_;
    }

    void getDamages(int &i) { i = damage; }
    void getHands(int &j)   { j = handsRequired; }

    void getInfo()
    {
        cout << "Weapon" << endl;
        Item::getInfo();
        cout << "Damage: " << damage << endl << "Hands required: " << handsRequired << endl;
    }

    int whatIs() { return 0; }  //weapon..return value: 0
};



class Armor: public Item{
private:
    int damageReduce;
public:
    Armor(string name_, int price_, int minLevel_, int damage_): Item(name_, price_, minLevel_)
    {
        damageReduce = damage_;
    }

    void getDamages(int &i) { i = damageReduce; }

    void getInfo()
    {
        cout << "Armor" << endl;
        Item::getInfo();
        cout << "Damage reduce: " << damageReduce << endl;
    }

    int whatIs() { return 1; }  //armor..return value: 1
};



class Potion : public Item {
private:
    int increaseSDA;
    string increaseType;
public:
    Potion(string name_, int price_, int minLevel_, int increase_,  string increaseType_): Item(name_, price_, minLevel_)
    {
        increaseSDA = increase_;
        increaseType = increaseType_;
    }

    void getDamages(int& i) { i = increaseSDA;  }
    void getType(string& i) { i = increaseType; }

    void getInfo()
    {
        cout << "Potion" << endl;
        Item::getInfo();
        cout << "Skill increase: +" << increaseSDA << " " << increaseType << endl;
    }

	int whatIs() { return 2; }  //potion..return value: 2
};
