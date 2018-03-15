#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <climits>
#include "Grid.h"

Grid *createGrid();                 //read map from files and create the grid
void menu(int, Hero **, Grid *);    //player controls heroes actions via menu


int main()
{
    srand(time(NULL));

    //create and display map

    Grid *G = createGrid();
    G->displayMap();

    //create heroes

    const string Warriors[]  = {"Aragorn", "Boromir", "Frodo Baggins"};
    const string Sorcerers[] = {"Saruman the White", "Radagast", "Morinehtar the one blue wizard"};
    const string Paladins[]  = {"Legolas", "Galadriel", "Gimli"};

    int heroes = rand()%3 + 1;
    Hero **heroesArray = new Hero*[heroes];
    for(int i=0; i<heroes; i++)
    {
        int WSP = rand()%3;     //WSP stands for Warrior Sorcerer Paladin
        if(WSP == 0)
            heroesArray[i] = new Warrior(Warriors[i], 1, 100, 200, 60, 10, 50, 4);
        else if(WSP == 1)
            heroesArray[i] = new Sorcerer(Sorcerers[i], 1, 200, 400, 30, 10, 100, 4);
        else
            heroesArray[i] = new Paladin(Paladins[i], 1, 300, 100, 80, 10, 80, 4);
    }

    //initial equipment (weapons & armors & potions - spells must be bought)

    Item *w1= new Weapon(20, 1, "Crystal Sword", 40, 1);
	Item *a1= new Armor("Spiritual Shield", 30, 1, 40);
	Item *p1= new Potion("Candle of Life", 50, 1, 200, "dexterity");

	heroesArray[0]->addToInventory(w1);
	heroesArray[0]->addToInventory(a1);
	heroesArray[0]->addToInventory(p1);

	if(heroes >= 2)
    {

		Item *w2= new Weapon(30, 1, "Master Sword", 50, 2);
		Item *a2=  new Armor("Marching Shield", 50, 1, 60);
		Item *p2=  new Potion("Dark Matter", 100, 3, 200, "agility");

		heroesArray[1]->addToInventory(w2);
		heroesArray[1]->addToInventory(a2);
		heroesArray[1]->addToInventory(p2);
	}
	if(heroes == 3)
    {
		Item *w3= new Weapon(40, 2, "Prism Steel", 70, 3);
		Item *a3=  new Armor("Spiritual Shield", 70, 2, 100);
		Item *p3=  new Potion("Three Stars", 200, 3, 400, "strength");

		heroesArray[2]->addToInventory(w3);
		heroesArray[2]->addToInventory(a3);
		heroesArray[2]->addToInventory(p3);
	}

	//display menu options

	menu(heroes, heroesArray, G);

	//delete heroes

	for(int i=0; i<heroes; i++)
        delete heroesArray[i];
    delete[] heroesArray;

	return 0;
}



Grid *createGrid()
{
    char choice = ' ', fname[50];
	ifstream file;

	#ifdef __linux__
		cout << "\033[1;36mMap selection\033[0m\n";
	#else
		cout << "Map selection" << endl;
	#endif

	while(1)
    {
		cout << "Choose d for default grid or c for custom: ";
		cin >> choice;
		cin.ignore(INT_MAX, '\n');

		if(choice == 'd')
        {
            file.open("5x10map.txt");
            if(!file)
                cout << "Cannot open file" << endl;
            else break;
		}
		else if(choice == 'c')
		{
			cout << "Give the name of the file: ";
			cin >> fname;
			file.open(fname);
            if(!file)
                cout << "Cannot open file" << endl;
            else break;
		}
		else cout << "Wrong choice...try again" << endl;
	}

	int n, m;
	file >> n >> m;

	char **A = new char*[n];
	for(int i=0; i<n; i++)
    {
		A[i] = new char[m];
	}

	for(int i=0; i<n; i++)
    {
		for(int j=0; j<m; j++)
			file >> A[i][j];
	}
	file.close();

	Grid *G = new Grid(n, m, A);

	for(int i=0; i<n; i++)
    {
		delete A[i];
	}
	delete[] A;

	return G;
}



void menu(int heroes, Hero **heroesArray, Grid *G)
{
	while(1)
    {

        #ifdef __linux__
		cout << "\033[1;36m\nMenu Options\033[0m\n";
        #else
            cout << endl << "Menu Options" << endl;
        #endif
		cout << "|- display MAP (type \"map\")              |" << endl
    	     << "|- MOVE heroes (type \"move\" + direction) |" << endl
    	     << "|- POTION use (type \"potion\")            |" << endl
             << "|- EQUIP from inventory (type \"equip\")   |" << endl
    	     << "|- heroes INFORMATION (type \"info\")      |" << endl
    	     << "|- change MAP (type \"travel\")            |" << endl
    	     << "|- QUIT game (type \"quit\")               |" << endl
    	     << "Please select: ";

		string answer;
		cin >> answer;
		if(answer == "quit")
			return;
		else if(answer == "map")
        {
			G->displayMap();
		}
		else if(answer == "move")
		{
			string direction = "down";
			cin >> direction;
			if(direction == "up" || direction == "down" || direction == "left" || direction == "right")
			{
				if(G->moveHeroes(direction, heroes, heroesArray) == 0)
					cout << "Cannot move the heroes there" << endl;
			}
			else
				cout << "Not a valid direction" << endl;
		}
		else if(answer == "potion")
    	{
    		for(int i=0;i<heroes;i++) {
				cout << "Hero " << i << ": " << heroesArray[i]->getName() << endl;
			}
			cout << "Choose hero (number): ";
			int num;
			cin >> num;
			if(num >= 0 && num < heroes) {
				heroesArray[num]->checkInventory();
    	    	while(1)
    	    	{
    	        	cout << "Select a potion from inventory (number) or return to Menu Options (type \"-1\"): ";

    	        	int choice;
    	        	cin.clear();
    	        	cin.ignore(INT_MAX, '\n');
    	        	cin >> choice;
    	        	if(choice == -1)
    	        	    break;
    	        	else if(heroesArray[num]->itemValidation(choice, 2) == 1)
    	        	{
    	        	    heroesArray[num]->use(choice);
    	        	    break;
    	        	}
    	        	else
    	        	    cout << "Wrong selection" << endl;
    	    	}
    		}
    	}
		else if(answer == "equip")
		{
			for(int i=0;i<heroes;i++) {
				cout << "Hero " << i << ": " << heroesArray[i]->getName() << endl;
			}
			cout << "Choose hero (number): ";
			int num;
			cin >> num;
			if(num >= 0 && num < heroes) {
				heroesArray[num]->checkInventory();
				while(1)
    	    	{
    	    		cout << "Select weapon or armor to equip (number) or return to Menu Options (type \"-1\"): ";
    	    		int choice;
    	    		cin.clear();
    	    		cin.ignore(INT_MAX, '\n');
    	    		cin >> choice;
    	    		if(choice == -1)
    	    		    break;
    	    		else if(heroesArray[num]->equip(choice) == 1)
    	    		{
    	    		    cout << "Equiped successfully" << endl;
    	    		    break;
    	    		}
    	    		else
    	    		    cout << "Wrong selection. Please choose a weapon or armor from the Items Inventory." << endl;
    			}
			}
			else
			{
				cout << "Wrong selection" << endl;
			}
		}
        else if(answer == "info")
        {
            for(int i=0; i<heroes; i++)
            {
                heroesArray[i]->displayInfo();
                cout << endl;
            }
        }
        else if(answer == "travel")
        {
        	delete G;
        	G = createGrid();
		}
		else
			cout << "Not a valid option" << endl;
	}
}
