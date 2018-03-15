#include <cstdlib>
#include <ctime>
#include <climits>
#include "Grid.h"


void Square::printSquare()
{
	if(hasHero)
		cout << "c";
	else
		cout << characters[type];
}



void Grid::displayMap()     //function for printing map
{
    string frame = "*";


    #ifdef __linux__
		cout << "\033[1;36mGame map\033[0m\n";
	#else
		cout << "Game map" << endl;
	#endif

	for(int i=0; i<getWidth()+4; i++)
        cout << frame;
    cout << endl;

	for(int i=0;i<length;i++)
    {
    	cout << frame << " ";
		for(int j=0; j<width; j++)
			grid[i][j]->printSquare();
		cout << " " << frame << endl;
	}

    for(int i=0; i<getWidth()+4; i++)
        cout << frame;
	cout << endl << endl;
}



bool Grid::moveHeroes(string direction, int heroes, Hero **heroesArray) //function for moving the heroes on map
{
    //move heroes...

    int coordinateX = 0, coordinateY = 0, foundFlag = 0;
	for(int i=0;i<length;i++)                                           //scan the whole map
    {
		for(int j=0;j<width;j++)
		{
			if(grid[i][j]->hasHero)                                     //if heroes found..
			{
				if(direction == "up")                                   //..move them UP
				{
					if(i-1 >= 0 && grid[i-1][j]->type != nonAccessible) //accessibility check
					{
						grid[i-1][j]->hasHero = true;
						grid[i][j]->hasHero = false;
						coordinateX = i-1;
						coordinateY = j;
					}
					else
                        return 0;
				}
				else if(direction == "down")                            //...move them DOWN
				{
					if(i+1 < length && grid[i+1][j]->type != nonAccessible)
					{
                        grid[i+1][j]->hasHero = true;
						grid[i][j]->hasHero = false;
						coordinateX = i+1;
						coordinateY = j;
					}
					else
                        return 0;
				}
				else if(direction == "left")                            //...move them LEFT
				{
					if(j-1 >= 0 && grid[i][j-1]->type != nonAccessible)
					{
						grid[i][j-1]->hasHero = true;
						grid[i][j]->hasHero = false;
						coordinateX = i;
						coordinateY = j-1;
					}
					else
                        return 0;
				}
				else if(direction == "right")                           //...move them RIGHT
                {
					if(j+1 < width && grid[i][j+1]->type != nonAccessible)
					{
						grid[i][j+1]->hasHero = true;
						grid[i][j]->hasHero = false;
						coordinateX = i;
						coordinateY = j+1;
					}
					else
                        return 0;
				}
				else
					return 0;

                foundFlag = 1;
                break;
			}
		}
		if(foundFlag == 1)
            break;
	}

	//check the type of the new position

    if(grid[coordinateX][coordinateY]->type == common)                  //COMMON square..check if going into battle
    {
        if(rand()%100 < 50)                                             //possibility to engage in battle
            battle(heroes, heroesArray);
        return 1;
    }
    else if(grid[coordinateX][coordinateY]->type == market)             //MARKET square..buy/sell options
    {
        #ifdef __linux__
            cout << "\033[1;35mWelcome to the Marketplace!\033[0m\n";
        #else
            cout << "Welcome to the Marketplace!" << endl;
        #endif

        while(1)
		{
		    #ifdef __linux__
                cout << "\033[1;36mMarket Options\033[0m\n";
            #else
                cout << "Market Options" << endl;
            #endif

        	cout << "|-	BUY ITEM (type \"buy\")       |" << endl
                 << "|-	SELL ITEM (type \"sell\")     |" << endl
                 << "|-	LEAVE MARKET (type \"leave\") |" << endl
                 << "Please select: ";

			string choice;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> choice;

			if(choice == "leave")
				break;
    		else if(choice == "buy" || choice == "sell")
        	{
        		int num;

        	    //print heroes and their money

				for(int i=0;i<heroes;i++)
                {
					cout << "Hero " << i << ": " << heroesArray[i]->getName();
					cout << " - " << heroesArray[i]->getMoney() << " $" << endl;
				}

				//..ask the number of the hero who buys/sells

				while(1)
				{
					cout << "Please type the number of the hero who buys/sells: ";
            		cin.clear();
            		cin.ignore(INT_MAX, '\n');
            		cin >> num;

            		if(num < 0 || num >= heroes)
            		    cout << "Wrong hero number. This is what happens when there is no GUI :(" << endl;
            		else break;
				}

				//..print items and spells in the market (for buy), else print the hero's inventory (for sell)

            	if(choice == "buy")
            	    gameMarket.show();
            	else
            	    heroesArray[num]->checkInventory();

	            //..ask for selection between items and spells

				cout << "You have " << heroesArray[num]->getMoney() << " $" << endl;
				cout << "Please select type (for item type \"I\" - for spell type \"S\"): ";
				char itemOrSpell;
        	    cin.clear();
        	    cin.ignore(INT_MAX, '\n');
        	    cin >> itemOrSpell;

        	    //..ask to specify the item

				cout << "Please type the number of the item/spell you choose: ";
				int number;
        	    cin.clear();
        	    cin.ignore(INT_MAX, '\n');
        	    cin >> number;

        	    //..buy/sell process

        	    if(choice == "buy")
        	        if(gameMarket.buy(itemOrSpell, number, *heroesArray[num]))
						cout << "Item/Spell was successfully bought" << endl;
					else
						cout << "Cannot buy item/spell" << endl;
        	    else
        	    	if(gameMarket.sell(itemOrSpell, number, *heroesArray[num]))
        	        	cout << "Item/Spell was successfully sold" << endl;
        	        else
        	        	cout << "Cannot sell item/spell" << endl;
        	}
        	else
        	    cout << "Wrong option" << endl;
		}
        return 1;
    }
    return 0;
}



void Grid::battle(int heroes, Hero **heroesArray)
{
    #ifdef __linux__
        cout << "\033[1;33m\nSuddenly some wild monsters appear! Prepare for battle!\033[0m\n";
    #else
        cout << endl << "Suddenly some wild monsters appear! Prepare for battle!" << endl;
    #endif

	//monsters creation

    Monster **monstersArray = new Monster*[heroes];
    for(int i=0; i<heroes; i++)
    {
        int finalLevel = 1;     //monsters' level is approximately close to this of the hero they fight against
        do                      //there are only 4 levels (1 to 4)
        {
            int l = heroesArray[i]->getLevel();
            int c[]={l-1, l, l+1};
            finalLevel = c[rand()%3];
	    }while(finalLevel == 0 || finalLevel == 5);

    	int DES = rand()%3;     //DES stands for Dragon Exoskeleton Spirit
    	if(DES == 0)
    	    monstersArray[i] = new Dragon("White Dragon", finalLevel, 90);
    	else if(DES == 1)
    	    monstersArray[i] = new Exoskeleton("Skeleton", finalLevel, 120);
    	else
    	    monstersArray[i] = new Spirit("Invisible Spirit", finalLevel, 60);
    }

    //store the initial healthPower status, money of the heroes

    int health[heroes], money[heroes];
    for(int i=0; i<heroes; i++)
    {
        health[i] = heroesArray[i]->getHealth();
        money[i] = heroesArray[i]->getMoney();
    }

    //spell variables. Initial and final

    int initial[heroes] = {0}, spellRounds[heroes] = {0};
    char kindOf[heroes] = {0};

    //battle begins

    int rounds = 1, deadHeroes = 0, deadMonsters = 0;
	bool flag = false;
    while(deadHeroes < heroes && deadMonsters < heroes )                       //battle until either heroes or monsters die
    {
        #ifdef __linux__
            cout << "\033[1;34mROUND \033[0m" << rounds << endl;
        #else
            cout << endl << "ROUND " << rounds << endl;
        #endif

        #ifdef __linux__
            cout << "\033[1;32mHeroes turn\033[0m\n";
        #else
            cout << endl << "Heroes turn" << endl;
        #endif

    	for(int i=0; i<heroes; i++)                                            //heroes turn..for every hero select action
    	{
    	    if(heroesArray[i]->passOut())                                      //if hero has pass'ed'Out() we move to the next one
                continue;

    	    cout << "	Hero " << heroesArray[i]->getName() << endl;
    	    string choice;
    	    while(1)
    	    {
                #ifdef __linux__
                    cout << "\033[1;36mBattle Options\033[0m\n";
                #else
                    cout << "Battle Options" << endl;
                #endif

    	    	cout << "|-	ATTACK (type \"attack\")              |" << endl
    	        	 << "|-	CAST SPELL (type \"spell\")           |" << endl
    	             << "|-	POTION USE (type \"potion\")          |" << endl
    	             << "|-	DISPLAY STATS (type \"stats\")        |" << endl
    	             << "|-	CHANGE WEAPON/ARMOR (type \"change\") |" << endl
    	             << "Please select: ";

    	    	cin >> choice;

    	    	int availableForAttack = 0;                                     //find first available monster for attack..
                    for(int j=0; j<heroes; j++)                                 //we will use it for "attack" and "spell"
                        if(!monstersArray[j]->passOut())
                        {
                            availableForAttack = j;
                            break;
                        }

    	        if(choice == "attack")
    	        {

    	        	heroesArray[i]->attack(*monstersArray[availableForAttack]); //..attack and check if passed out
    	        	if(monstersArray[availableForAttack]->passOut())
    	        	{
    	        		cout << "Monster " << monstersArray[availableForAttack]->getName() << " passed out" << endl;
    	        		deadMonsters++;
					}
					break;
    	        }
    	        else if(choice == "spell")                                     //use a spell to attack.  Spell must exist
    	        {
    	            heroesArray[i]->checkInventory();
    	            bool flag = false;
    	            while(1)
    	            {
    	                cout << "Select a spell from inventory (number) or return to battle options (type \"-1\"): ";

    	                int choice;
    	                cin.clear();
    	                cin.ignore(INT_MAX, '\n');
    	                cin >> choice;

    	                if(choice == -1)
    	                	break;
    	                else if(heroesArray[i]->spellValidation(choice) == 1)   //check for proper input and..castSpell
    	                {
    	                    heroesArray[i]->castSpell(choice, *monstersArray[availableForAttack], initial[i],\
                                                    spellRounds[i], kindOf[i]);
                            flag = true;
							spellRounds[i] += rounds;                           //spell is active from current round
                            if(monstersArray[availableForAttack]->passOut())    //check if monster passed out
    	        			{
    	        				cout << "Monster " << monstersArray[availableForAttack]->getName() << " passed out" << endl;
    	        				deadMonsters++;
							}
    	                    break;
    	                }
    	                else
    	                    cout << "Wrong selection" << endl;
    	            }
    	            if(flag) break;
    	        }
    	        else if(choice == "potion")                                     //use a potion
    	        {
    	            heroesArray[i]->checkInventory();
    	            bool flag = false;
    	            while(1)
    	            {
    	                cout << "Select a potion from inventory (number) or return to Battle Options (type \"-1\"): ";

    	                int choice;
    	                cin.clear();
    	                cin.ignore(INT_MAX, '\n');
    	                cin >> choice;

    	                if(choice == -1)
    	                	break;
    	                else if(heroesArray[i]->itemValidation(choice, 2) == 1) //check for proper input
    	                {
    	                    heroesArray[i]->use(choice);
    	                    flag = true;
    	                    break;
    	                }
    	                else
    	                    cout << "Wrong selection" << endl;
    	            }
    	            if(flag) break;
    	        }
    	        else if(choice == "stats")                                      //display heroes and monsters stats
    	        {

                    #ifdef __linux__
                        cout << "\033[1;36m\nHeroes\033[0m\n";
                    #else
                        cout << endl << "Heroes" << endl;
                    #endif

    	        	for(int i=0;i<heroes;i++)
                    {
    	        		heroesArray[i]->displayInfo();
    	        		cout << endl;
					}

					#ifdef __linux__
                        cout << "\033[1;36m\nMonsters\033[0m\n";
                    #else
                        cout << endl << "Monsters" << endl;
                    #endif

					for(int i=0;i<heroes;i++)
                    {
						monstersArray[i]->displayInfo();
						cout << endl;
					}
					break;
				}
				else if(choice == "change")                                     //change hero's equipment
				{
					heroesArray[i]->checkInventory();
					bool flag = false;
					while(1)
    	            {
    	                cout << "Select weapon or armor to equip (number) or return to Battle Options (type \"-1\"): ";

    	                int choice;
    	                cin.clear();
    	                cin.ignore(INT_MAX, '\n');
    	                cin >> choice;

    	                if(choice == -1)
    	                	break;
    	                else if(heroesArray[i]->equip(choice) == 1)
    	                {
    	                    cout << "Equiped successfully" << endl;
    	                    flag = true;
    	                    break;
    	                }
    	                else
    	                    cout << "Wrong selection. Please choose a weapon or armor from the ITEMS Inventory" << endl;
    	            }
    	            if(flag) break;
				}
				else if(choice == "win")                                        //a little hack for player's convenience :)
				{
					cout << "Hack activated ;)" << endl;
					deadMonsters = heroes;
					flag = true;
					break;
				}
    	        else
    	            cout << "Wrong choice...try again" << endl;
    	    }
    	    if(flag) break;
    	}

    	if(deadMonsters >= heroes)     //check if all monsters are dead ("heroes" is the number of monsters)
            break;

    	#ifdef __linux__
            cout << "\033[1;31mMonsters turn\033[0m\n";		                   //monsters attack
        #else
            cout << endl << "Monsters turn" << endl;
        #endif

    	for(int i=0; i<heroes;i++)
        {
        	if(!monstersArray[i]->passOut())                                   //check if monster has not pass'ed'Out() and..attack
        	{
        		cout << "	Monster " << monstersArray[i]->getName() << endl;

        		int availableForAttack = 0;                                   //find first available hero for attack..
                for(int j=0; j<heroes; j++)
                    if(!heroesArray[j]->passOut())
                    {
                        availableForAttack = j;
                        break;
                    }

    			monstersArray[i]->attack(*heroesArray[availableForAttack]);
    			if(heroesArray[availableForAttack]->passOut())
    			{
    				cout << "Hero " << heroesArray[availableForAttack]->getName() << " passed out" << endl;
    				deadHeroes++;
				}
			}
		}

        //give heroes magic power and health power

		for(int i=0; i<heroes; i++)
        {
            if(heroesArray[i]->passOut() == false)
            {
                heroesArray[i]->setHealth(heroesArray[i]->getHealth() + 50);
                heroesArray[i]->addMagicPower(15);
            }
        }

        //spell check before the next round begins

        for(int i=0; i<heroes; i++)
        {
            if(rounds > spellRounds[i]) //"spellRounds" count starts from 1
            {
                if(kindOf[i] == 'i')
                    monstersArray[i]->setDamage(initial[i]);
                else if(kindOf[i] == 'f')
                    monstersArray[i]->setDefence(initial[i]);
                else if(kindOf[i] == 'l')
                    monstersArray[i]->setAvoidance(initial[i]);
            }
        }

		rounds++;
	}

    //battle ends...final outcome

	if(deadHeroes == heroes)
    {
        #ifdef __linux__
            cout << "\033[1;33mHeroes lost!\033[0m\n";
        #else
            cout << endl << "Heroes lost!" << endl;
        #endif

		//restore heroes' healthPower at the half of the initial one

    	for(int i=0; i<heroes; i++)
            heroesArray[i]->setHealth(health[i]/2);

		//heroes lost so they lose half of their money

        for(int i=0; i<heroes; i++)
            heroesArray[i]->setMoney(money[i]/2);
    }
	else
    {
        #ifdef __linux__
            cout << "\033[1;33mHeroes won!\033[0m\n";
        #else
            cout << endl << "Heroes won!" << endl;
        #endif

        //awards: money & experience
        //the number of heroes equals the number of monsters..So all heroes of the same level receive the same money

        for(int i=0; i<heroes; i++)
        {
            int level = heroesArray[i]->getLevel();             //minimum level: 1
            if(level == 1)
            {
            	if(heroesArray[i]->passOut())
                	heroesArray[i]->setHealth(health[i]/2);
                else
                	heroesArray[i]->setHealth(heroesArray[i]->getHealth() + 100);

                heroesArray[i]->setMoney(money[i] + 100);
                heroesArray[i]->addMagicPower(30);
                heroesArray[i]->addExperience(50);

            }
            else if(level == 2)
            {
            	if(heroesArray[i]->passOut())
                	heroesArray[i]->setHealth(health[i]/2);
                else
                	heroesArray[i]->setHealth(heroesArray[i]->getHealth() + 200);

                heroesArray[i]->setMoney(money[i] + 200);
                heroesArray[i]->addMagicPower(50);
                heroesArray[i]->addExperience(100);

            }
            else if(level == 3)
            {
            	if(heroesArray[i]->passOut())
                	heroesArray[i]->setHealth(health[i]/2);
                else
                	heroesArray[i]->setHealth(heroesArray[i]->getHealth() + 400);

                heroesArray[i]->setMoney(money[i] + 400);
                heroesArray[i]->addMagicPower(70);
                heroesArray[i]->addExperience(150);

            }
            else if(level == 4)                                 //maximum level: 4
            {
            	if(heroesArray[i]->passOut())
                	heroesArray[i]->setHealth(health[i]/2);
                else
                	heroesArray[i]->setHealth(heroesArray[i]->getHealth() + 500);

                heroesArray[i]->setMoney(money[i] + 500);
                heroesArray[i]->addMagicPower(100);
                heroesArray[i]->addExperience(250);

            }
            else
            {
            	if(heroesArray[i]->passOut())
                	heroesArray[i]->setHealth(health[i]/2);
			}
            heroesArray[i]->levelUp();
        }
    }

    //monsters delete :)

    for(int i=0; i<heroes; i++)
        delete monstersArray[i];
    delete[] monstersArray;
}
