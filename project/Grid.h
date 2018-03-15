#include <iostream>
#include <string>
#include "Market.h"

using namespace std;

enum SquareType{ nonAccessible, market, common};                    //square types..
string const ST_string[] = {"nonAccessible", "market", "common"};   //..their names
char const characters[] = {'x', 'm', '.'};                          //..and their symbols


class Square{
private:

public:
	SquareType type;
	bool hasHero;
	Square(SquareType type_) : type(type_)
	{
		hasHero = false;
	}
	void printSquare();
};



class Grid{     //Grid is an 2D array of Squares
private:
	int length;
	int width;
	marketClass gameMarket;
	Square *** grid;
public:
	Grid(int length_, int width_, char **grid_ ) : length(length_), width(width_)
	{
		int i, j;
		SquareType t;
		bool flag = false;
		grid = new Square**[length];                                //grid creation
		for(i=0;i<length;i++)
        {
			grid[i] = new Square*[width];
			for(j=0;j<width;j++)
			{
				if(grid_[i][j] == characters[nonAccessible])
                    t = nonAccessible;
				else if(grid_[i][j] == characters[market])
                    t = market;
				else if(grid_[i][j] == characters[common])
                    t = common;
				else
                {
					flag = true;
					t = nonAccessible;
				}
				grid[i][j] = new Square(t);
			}
		}
		grid[0][0]->hasHero = true;
		if(flag)
            cout << "Some symbols of the map were not recognized. Some squares may be inaccessible to heroes." << endl;
	}

	~Grid()
	{
		int i;
		for(i=0;i<length;i++)
			delete grid[i];
		delete[] grid;
	}

	void displayMap();                                              //print grid elements

    int getWidth() { return width; }

    bool moveHeroes(string, int, Hero**);                           //move heroes within map

    void battle(int, Hero **);                                      //heroes fight against monsters
};
