#include <cstdlib>
#include <ctime>
#include "Living.h" //includes "Item.h"

//section A: functions of CLASS HERO

Hero::Hero(string name_, int level_, int healthPower_, int magicPower_, int money_, int maxItems_, int upgradeEvery_, \
    int maxLevel_): Living(name_, level_, healthPower_)
{
    experience = 0; //default experience

    strength = 0;   //about to change at derived classes
    dexterity = 0;
    agility = 0;

    magicPower = magicPower_;
    money = money_;
    maxItems = maxItems_;
    upgradeEvery = upgradeEvery_;
    maxLevel = maxLevel_;

    handLeft = NULL;
    handRight = NULL;
    armor = NULL;

    inventory = new Item*[maxItems];
    for(int i=0; i<maxItems; i++)
        inventory[i] = NULL;

    inventorySpells = new Spell*[maxItems];
    for(int i=0; i<maxItems; i++)
        inventorySpells[i] = NULL;
}



Hero::~Hero()
{
	for(int i=0; i<maxItems; i++)                   //delete hero's items
		if(inventory[i] != NULL)
        	delete inventory[i];
    delete[] inventory;

    for(int i=0; i<maxItems; i++)                   //delete hero's spells
		if(inventorySpells[i] != NULL)
        	delete inventorySpells[i];
    delete[] inventorySpells;
}



void Hero::checkInventory()
{
    cout << endl << "Items Inventory" << endl;      //print items
    for(int i=0; i<maxItems; i++)
    {
        if(inventory[i] != NULL)
        {
        	cout << "Item " << i << endl;
        	inventory[i]->getInfo();
        	cout << endl;
		}
    }

    cout << endl << "Spells Inventory" << endl;     //print spells
    for(int i=0; i<maxItems; i++)
    {
        if(inventorySpells[i] != NULL)
        {
        	cout << "Spell " << i << endl;
        	inventorySpells[i]->getInfo();
        	cout << endl;
		}
    }
}



bool Hero::addToInventory(Item* item)               //add an item to "inventory" (used for market purchases)
{
    for(int i=0; i<maxItems; i++)
    {
        if(inventory[i] == NULL)
        {
            inventory[i] = item;
            return 1;
        }
    }
    return 0;
}



bool Hero::addToInventorySpells(Spell* item)        //add a spell to "inventorySpells" (used for market purchases)
{
    for(int i=0; i<maxItems; i++)
    {
        if(inventorySpells[i] == NULL)
        {
            inventorySpells[i] = item;
            return 1;
        }
    }
    return 0;
}


Item* Hero::removeFromInventory(int i)              //remove an item from "inventory" (used for market sells)
{
    if(i >= 0 && i < maxItems && inventory[i] != NULL)
    {
        Item *temp= inventory[i];
        inventory[i] = NULL;
        return temp;
    }
    return NULL;
}


Spell* Hero::removeFromInventorySpells(int i)       //remove a spell from "inventorySpells" (used for market sells)
{
    if(i >= 0 && i < maxItems && inventorySpells[i] != NULL)
    {
        Spell *temp= inventorySpells[i];
        inventorySpells[i] = NULL;
        return temp;
    }
    return NULL;
}



void Hero::use(int i)                               //potion use
{
    if(getLevel() < inventory[i]->getMinLevel())    //check for appropriate level
        cout << "Cannot use item until level "
             << inventory[i]->getMinLevel() << endl;
    else
    {
        string type;
        inventory[i]->getType(type);

        int increase;
        inventory[i]->getDamages(increase);
        increaseAbility(type, increase);            //increase hero's ability..
        delete inventory[i];                        //..and delete potion
        inventory[i] = NULL;
        cout << "Potion  used" << endl;
    }
}



bool Hero::equip(int i)                             //equip hero with items
{
	if(i>=0 && i<maxItems && inventory[i] != NULL)
	{
		if(this->getLevel() >= inventory[i]->getMinLevel())
		{
			if(inventory[i]->whatIs() == 0)         //weapon
    		{
    	    	int hands;
    	    	inventory[i]->getHands(hands);

	        	if(hands == 1)                      //one hand weapon
	        	{
            		if(handLeft == handRight)       //both NULL or hero has a two-handed weapon
            		{
            		    Item *temp = handLeft;
            		    handLeft = inventory[i];
            		    handRight = NULL;
            		    inventory[i] = temp;
            		}
            		else if(handLeft == NULL)       //check if left hand available
            		{
            	    	Item *temp = handLeft;
            	    	handLeft = inventory[i];
            	    	inventory[i] = temp;
            		}
            		else                            //...else grab it with the right hand
            		{
            	    	Item *temp = handRight;
            	    	handRight = inventory[i];
            	    	inventory[i] = temp;
            		}
        		}
        		else                                //a two hand weapon
        		{
            		Item *temp = handLeft, *temp1 = handRight;
            		handLeft = handRight = inventory[i];
            		inventory[i] = temp;
            		if(temp != temp1)
            		    addToInventory(temp1);
        		}
    		}
    		else if(inventory[i]->whatIs() == 1)    //armor
    		{
        		Item *temp = armor;
        		armor = inventory[i];
        		inventory[i] = temp;
    		}
    		else
    		    return 0;
    		return 1;
		}
		else
		{
			cout << "Can't equip item until level " << inventory[i]->getMinLevel() << endl;
			return 0;
		}
	}
	else
		return 0;
}


//Section B: levelUp() PURE VIRTUAL implementation

void Warrior::levelUp()
{
    int level = getLevel(), experience_ , upgradeEvery_;
    isLevelUp(experience_, upgradeEvery_);

    if( level < getMaxLevel() && experience_ >= upgradeEvery_)
    {
        setLevel(++level);

        int s, d, a;
        getSDA(s, d, a);

        s += 120;
        d += 60;
        a += 120;

        setSDA(s, d, a);

        cout << "Congratulations Warrior! Updated at level " << level << endl;
    }
}



void Sorcerer::levelUp()
{
    int level = getLevel(), experience_ , upgradeEvery_;
    isLevelUp(experience_, upgradeEvery_);

    if( level < getMaxLevel() && experience_ >= upgradeEvery_)
    {
        setLevel(++level);

        int s, d, a;
        getSDA(s, d, a);

        s += 60;
        d += 120;
        a += 120;

        setSDA(s, d, a);

        cout << "Congratulations Sorcerer! Updated at level " << level << endl;
    }
}



void Paladin::levelUp()
{
    int level = getLevel(), experience_ , upgradeEvery_;
    isLevelUp(experience_, upgradeEvery_);

    if( level < getMaxLevel() && experience_ >= upgradeEvery_)
    {
        setLevel(++level);

        int s, d, a;
        getSDA(s, d, a);

        s += 120;
        d += 120;
        a += 60;

        setSDA(s, d, a);

        cout << "Congratulations Paladin! Updated at level " << level << endl;
    }
}



void Hero::attack(Monster& m)                       //for one battle round
{
    //hero attacks

    int damage = strength, left = 0, right = 0, finalDamage;

    if(handLeft != NULL)
        handLeft->getDamages(left);
    if(handRight != NULL)
        handRight->getDamages(right);
    if(handLeft == handRight)
        damage += left;
    else
    	damage += left + right;

    //monster has a probability to avoid the attack

    int probability;
    m.getAvoidance(probability);

    if(rand()%100 < probability)
    	cout << "The monster avoided your attack" << endl;
	else
	{
		finalDamage = m.getHurt(damage);
		cout << "Attack successful: +" << finalDamage << " damage dealt to "
                                       << m.getName() << " by " << this->getName() << endl;
	}
}



void Hero::castSpell(int choice, Monster &m, int &initial_, int &rounds_, char &kindOf_)
{
    //hero uses a spell to attack

    int energy = inventorySpells[choice]->getEnergyRequired();
    if(magicPower >= energy)
    {
        magicPower -= energy;

        //damage depends on "dexterity" (class Hero) and "damageRange" (class Spell)

        int damage = inventorySpells[choice]->getDamageRange();
        int range = dexterity*(0.5) + damage*(0.5);
        if(range > damage)
            range = damage;
        m.getHurt(damage);
        cout << "+ " << damage << " damage on " << m.getName() << endl;

        int init, reduce = 30;                      //reduce: default value. Customize if desired

        kindOf_ = inventorySpells[choice]->whatSpellIs();
        if( kindOf_ == 'i')
        {
            m.getDamage(init);
            initial_ = init;
            m.setDamage(init - reduce);             //ice spell: reduce "damageRange" of monster

            cout << "Spell reduced damage range of " << m.getName() << " by " << reduce << endl;
        }
        else if( kindOf_ == 'f')
        {
            m.getDefence(init);
            initial_ = init;
            m.setDefence(init - reduce);            //fire spell: reduce "defenceAmount" of monster

            cout << "Spell reduced defence amount of " << m.getName() << " by " << reduce << endl;
        }
        else if( kindOf_ == 'l')
        {
            m.getAvoidance(init);
            initial_ = init;
            m.setAvoidance(init - reduce);          //lightning spell: reduce "avoidancePossibility" of monster

            cout << "Spell reduced avoidance possibility of " << m.getName() << " by " << reduce << endl;
        }
        rounds_ = inventorySpells[choice]->getRounds();

        delete inventorySpells[choice];             //spell is deleted after use
    }
    else
        cout << "Cannot use this spell. Sorry :(" << endl;
}


//Section C: functions of CLASS MONSTER

void Monster::attack(Hero& h)
{
	int damage, finalDamage;
	damage = rand()%damageRange;
	finalDamage = h.getHurt(damage);
	cout << this->getName() << " hit " << h.getName() << ". -" << finalDamage << " health." << endl;
}
