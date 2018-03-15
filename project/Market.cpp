#include "Market.h"

//the market contains a limited amount of items and spells

marketClass::marketClass()
{
    //maxItems: market items + items heroes have in case they decide to sell them

    maxItems = 21;
    items = new Item*[maxItems];

	//items (weapons)

    items[0] = new Weapon(20, 1, "Crystal Sword", 40, 1);
    items[1] = new Weapon(30, 1, "Master Sword", 50, 2);
    items[2] = new Weapon(40, 2, "Prism Steel", 70, 3);
    items[3] = new Weapon(70, 2, "Rod of Roses", 100, 4);

	//items (armors)

    items[4] = new Armor("Spiritual Shield", 30, 1, 40);
    items[5] = new Armor("Marching Shield", 50, 1, 60);
    items[6] = new Armor("Black Shield", 70, 2, 100);
    items[7] = new Armor("Platinum Shield", 100, 3, 200);

	//items (potions)

    items[8] = new Potion("Candle of Life", 50, 1, 200, "dexterity");
    items[9] = new Potion("Dark Matter", 100, 3, 200, "agility");
    items[10] = new Potion("Three Stars", 200, 3, 400, "strength");
    items[11] = new Potion("Wings to Discovery", 100, 3, 200, "strength");

    for(int i=12;i<maxItems; i++)       //Rest of store is empty
    	items[i] = NULL;

    //maxSpells: default value. Customize if desired

    maxSpells = 3;
    spells = new Spell*[maxSpells];

	//spells

    spells[0] = new FireSpell("Flame", 70, 1, 50, 90, 1);
    spells[1] = new IceSpell("Torch", 80, 2, 80, 100, 1);
    spells[2]  = new LightingSpell("Eruption", 100, 2, 90, 150, 1);
}



void marketClass::show()                //prints the items and spells exist in the market
{
    #ifdef __linux__
		cout << "\033[1;35mThis is the market! You can buy the following items and spells\033[0m\n";
	#else
		cout << endl << "This is the market! You can buy the following items and spells" << endl;
	#endif


    #ifdef __linux__
		cout << "\033[1;36mA. Items\033[0m\n";          //A. items
	#else
		cout << endl << "A. Items" << endl;
	#endif

    for(int i=0; i<maxItems; i++)
        if(items[i] != NULL)
        {
        	cout << "Item " << i << endl;
        	items[i]->getInfo();
        	cout << endl;
		}

    #ifdef __linux__
		cout << "\033[1;36mB. Spells\033[0m\n";         //B. spells
	#else
		cout << endl << "B. Spells" << endl;
	#endif

    for(int i=0; i<maxSpells; i++)
        if(spells[i] != NULL)
        {
        	cout << "Spell " << i << endl;
        	spells[i]->getInfo();
        	cout << endl;
		}
}



bool marketClass::buy(char choice, int number, Hero& hero)
{
	//hero buys something from the market. If purchase fails, return to market menu

    if(choice == 'i' || choice == 'I')                                          //1. buy an ITEM
    {
        if(number >= 0 && number < maxItems && items[number] != NULL)           //check for valid parameters
        {
            int heroMoney = hero.getMoney();

            //make sure the player wants to buy the item for the specified price

			cout << "Buy item for " << items[number]->getMoney() << " $?(yes/no) ";
			string answer;
			cin >> answer;

			if(answer == "no")
                return 0;
			else if(answer == "yes")
			{
				if(heroMoney >= items[number]->getMoney())                      //check if hero has enough money
            	{
            	    if(hero.addToInventory(items[number]) == 1)                 //check if added successfully..
            	    {
            	        hero.setMoney(heroMoney - items[number]->getMoney());   //..and receive payment
            	        items[number] = NULL;
            	        return 1;
            	    }
            	    else
            	        return 0;
            	}
            	else
            	{
            		cout << "Not enough money" << endl;
            		return 0;
				}
			}
            else
			{
				cout << "Invalid input" << endl;
    			return 0;
			}
        }
        else
        {
        	cout << "Wrong item number" << endl;
        	return 0;
		}
    }
    else if(choice == 's' || choice == 'S')                                     //2. buy a SPELL
    {
        if(number >= 0 && number < maxSpells && spells[number] != NULL)         //check for valid parameters
        {
            int heroMoney = hero.getMoney();

            //make sure the player wants to buy the spell for the specified price

            cout << "Buy spell for " << spells[number]->getMoney() << " $?(yes/no) ";
			string answer;
			cin >> answer;

			if(answer == "no")
				return 0;
			else if(answer == "yes")
			{
				if(heroMoney >= spells[number]->getMoney())                     //check if hero has enough money
            	{
            	    if(hero.addToInventorySpells(spells[number]) == 1)          //check if added successfully..
            	    {
            	        hero.setMoney(heroMoney - spells[number]->getMoney());  //..and receive payment
            	        items[number] = NULL;
            	        return 1;
            	    }
            	    else
            	        return 0;
            	}
            	else
            	{
            		cout << "Not enough money" << endl;
            		return 0;
				}
			}
            else
            {
            	cout << "Invalid input" << endl;
    			return 0;
			}
        }
        else
        {
        	cout << "Wrong spell number" << endl;
        	return 0;
		}
    }
    else
    {
    	cout << "Wrong item type" << endl;
    	return 0;
	}
	return 1;
}



bool marketClass::sell(char choice, int number, Hero& hero)
{
	//hero sells something to the market. If sell fails, return to market menu

    int firstMoney = hero.getMoney();

	if(choice == 'i' || choice == 'I')                                          //1. sell an ITEM
    {
    	int price = hero.getInventoryMoney(number);

    	//make sure the player wants to sell the item half its price

        cout << "Sell item for " << price/2 << " $?(yes/no) ";
		string answer;
		cin >> answer;
		if(answer == "no")
			return 0;
		else if(answer == "yes")
		{
			hero.setMoney(firstMoney + (price/2));                              //sell the item half its price..
			for(int i=0; i<maxItems; i++)
            if(items[i] != NULL)
            {
                items[i] = hero.removeFromInventory(number);                    //..and remove it from inventory
                break;
            }
		}
		else
		{
			cout << "Invalid input" << endl;
    		return 0;
		}
    }
    else if(choice == 's' || choice == 'S')                                     //2. sell a SPELL
    {
    	int price = hero.getInventoryMoneySpells(number);

    	//make sure the player wants to sell the spell half its price

        cout << "Sell spell for " << price/2 << " $?(yes/no) ";
		string answer;
		cin >> answer;
		if(answer == "no")
			return 0;
		else if(answer == "yes")
		{
			hero.setMoney(firstMoney + (price/2));                              //sell the spell half its price..
			for(int i=0; i<maxSpells; i++)
            if(spells[i] != NULL)
            {
                spells[i] = hero.removeFromInventorySpells(number);             //..and remove it from inventory
                break;
            }
		}
		else
		{
			cout << "Invalid input" << endl;
    		return 0;
		}
    }
    else
	{
    	cout << "Wrong type. Please select I/i or S/s" << endl;
    	return 0;
	}
	return 1;
}
