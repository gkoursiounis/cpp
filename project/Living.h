#include <iostream>
#include <string>
#include "Item.h"
#include "Spell.h"

using namespace std;

class Monster;

class Living{       //abstract base class
private:
    string name;
    int level;
    int healthPower;
public:
	Living(string name_, int level_, int healthPower_):
	    name(name_), level(level_), healthPower(healthPower_) {}
    virtual ~Living() {}

	//mutators

	void setLevel (int level_) { level = level_;  }
	void setHealth(int i)      { healthPower = i; }
	string getName()           { return name;     }

	//accessors

	int getLevel()  { return level;       }
	int getHealth() { return healthPower; }

	bool passOut()
	{
		if(healthPower == 0)
			return 1;
		return 0;
	}

    virtual int getHurt(int damage)
	{
		healthPower = healthPower - damage;
		if(healthPower < 0) healthPower = 0;
		return damage;
	}

	virtual void displayInfo()
	{
	    cout << "Name: " << name <<  endl << "Level: " << level << endl
             << "Health Power: " << healthPower << endl;
	}

	virtual void favouredAt() = 0;  //pure virtual
};



class Hero: public Living{          //abstract base class
private:
    int magicPower;

    int strength;
    int dexterity;
    int agility;

    int money;
    int experience;
    int upgradeEvery;               //levelUp() every time experience reaches "upgradeEvery"
    int maxLevel;                   //max level the "living" can reach

    int maxItems;                   //max items in every inventory
    Item **inventory;
    Spell **inventorySpells;

    Item *handLeft;
    Item *handRight;
    Item *armor;

public:
	Hero(string, int, int, int, int, int, int, int);
	~Hero();

	//mutators

    bool addToInventory(Item*);
    bool addToInventorySpells(Spell*);
    bool equip(int);

    Item *removeFromInventory(int i);
    Spell *removeFromInventorySpells(int i);

    void use(int);
    void castSpell(int, Monster&, int &, int &, char &);
    void attack(Monster&);

    void setMoney(int i)      { money = i; }
    void addMagicPower(int i) { magicPower += i; }
    void addExperience(int i) { experience += i; }

    void setSDA(int i, int j, int k)
    {
        strength = i;
        dexterity = j;
        agility = k;
    }

	//accessors

    void checkInventory();

    int getMaxLevel()   { return maxLevel; }
	int getMoney()      { return money; }

    int itemValidation(int position, int type)
    {
        return (position >= 0 && position < maxItems && inventory[position] != NULL && inventory[position]->whatIs() == type)? 1 : 0;
    }

    int spellValidation(int position)
    {
        return (position >= 0 && position < maxItems && inventorySpells[position] != NULL)? 1 : 0;
    }

    int getInventoryMoney(int i)
    {
        if(i>=0 && i<maxItems && inventory[i] != NULL)
            return inventory[i]->getMoney();
        return 0;
    }

    int getInventoryMoneySpells(int i)
    {
        if(i>=0 && i<maxItems && inventorySpells[i] != NULL)
            return inventorySpells[i]->getMoney();
        return 0;
    }

    int getHurt(int damage)
    {
    	int damageReduce = 0;
		if(armor != NULL)
    	    armor->getDamages(damageReduce);
    	if(damage > damageReduce)
    		return Living::getHurt(damage - damageReduce);
		else return 0;
	}

	void increaseAbility(string ability, int increase)
	{
		if(ability == "strength")
			strength += increase;
		else if(ability == "dexterity")
			dexterity += increase;
		else if(ability == "agility")
			agility += increase;
	}

    void getSDA(int &i, int &j, int &k)
    {
        i = strength;
        j = dexterity;
        k = agility;
    }

    void isLevelUp(int &k, int &l)
    {
        k = experience;
        l = upgradeEvery;
    }

    void displayInfo()
	{
	    Living::displayInfo();
        cout << "Magic Power: " << magicPower <<  endl << endl << "Strength: " << strength << endl
             << "Dexterity: " << dexterity << endl << "Agility: " << agility << endl << endl
             << "Money: " << money << endl << "Experience: " << experience << endl
             << "Upgrade every: " << upgradeEvery << endl << "Max level: " << maxLevel << endl << endl;
	}

    virtual void levelUp() = 0;     //pure virtual
};



class Warrior: public Hero{
public:
    Warrior(string name_, int level_, int healthPower_, int magicPower_, int money_, int maxItems_, int upgradeEvery_, \
        int maxLevel_): Hero(name_, level_, healthPower_, magicPower_, money_, maxItems_, upgradeEvery_, maxLevel_)
    {
        favouredAt();
    }

    void levelUp();
    void favouredAt() { setSDA(50, 10, 50); }
};



class Sorcerer: public Hero{
public:
    Sorcerer(string name_, int level_, int healthPower_, int magicPower_, int money_, int maxItems_, int upgradeEvery_, \
        int maxLevel_): Hero(name_, level_, healthPower_, magicPower_, money_, maxItems_, upgradeEvery_, maxLevel_)
    {
        favouredAt();
    }

    void levelUp();
    void favouredAt() { setSDA(10, 50, 50); }
};



class Paladin: public Hero{
public:
    Paladin(string name_, int level_, int healthPower_, int magicPower_, int money_, int maxItems_, int upgradeEvery_, \
        int maxLevel_): Hero(name_, level_, healthPower_, magicPower_, money_, maxItems_, upgradeEvery_, maxLevel_)
    {
        favouredAt();
    }

    void levelUp();
    void favouredAt() { setSDA(50, 50, 10); }
};



class Monster: public Living{       //abstract base class
private:
    int damageRange;
    int defenceAmount;
    int avoidancePossibility;
public:
    Monster(string name_, int level_, int healthPower_): Living(name_, level_, healthPower_)
    {
        damageRange = 0;
        defenceAmount = 0;
        avoidancePossibility = 0;
    }

    void setDamage(int i)    { damageRange = i; }
    void setDefence(int j)   { defenceAmount = j; }
    void setAvoidance(int k) { avoidancePossibility = k; }

    void getDamage(int &i)    { i = damageRange; }
    void getDefence(int &j)   { j = defenceAmount; }
    void getAvoidance(int &k) { k = avoidancePossibility; }

	void attack(Hero&);

	int getHurt(int damage)
	{
		if(damage > defenceAmount)
			return Living::getHurt(damage - defenceAmount);
		else
			return 0;
	}
};



class Dragon: public Monster{
public:
    Dragon(string name_, int level_, int healthPower_): Monster(name_, level_, healthPower_)
    {
        favouredAt();
    }

    void favouredAt() { setDamage(40); setDefence(5); setAvoidance(5); }
};



class Exoskeleton: public Monster{
public:
    Exoskeleton(string name_, int level_, int healthPower_): Monster(name_, level_, healthPower_)
    {
        favouredAt();
    }

    void favouredAt() { setDamage(5); setDefence(40); setAvoidance(5); }
};



class Spirit: public Monster{
public:
    Spirit(string name_, int level_, int healthPower_): Monster(name_, level_, healthPower_)
    {
        favouredAt();
    }

    void favouredAt() { setDamage(5); setDefence(5); setAvoidance(40); }
};
