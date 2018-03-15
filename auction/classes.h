#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>

using namespace std;

class artifacts{                        //abstract base class
private:
    int index;                          //data members practically const since we have no mutators
    string creator;
    int year;
public:
    artifacts(int ind, string cr, int y): index(ind), creator(cr), year(y)
        { cout << "Creating a instance of class artifacts" << endl; }
    virtual ~artifacts() { cout << "Destroying a instance of class artifacts" << endl << endl; }            //virtual

    void getIndex() const { cout << "Index: " << index << endl; }
    virtual void getInfo() const { cout << "Creator: " << creator << endl << "Year: " << year << endl; }    //virtual
    virtual int evaluate(string, string) = 0;                                                               //pure virtual
};




class masterpiece: public artifacts{    //abstract base class
private:
    string movement;
    string condition;
public:
    masterpiece(string mov, string con, int index, string creator, int year): artifacts(index, creator, year)
    {
        movement = mov;
        condition = con;
        cout << "Creating a instance of class masterpiece" << endl;
    }
    ~masterpiece() { cout << "Destroying a instance of class masterpiece" << endl; }

    void changeCondition(string newCon) { condition.clear(); condition = newCon; }      //"condition" can change, the
                                                                                        //rest of data members cannot
    void getInfo() const
    {
        artifacts::getInfo();
        cout << "Movement: " << movement << endl << "Condition: " << condition << endl;
    }
    string getMovement() const { return movement; }
    string getCondition() const { return condition; }
};




class paintings: public masterpiece{
private:
    int length;                         //in cm
    int width;                          //in cm
    string technique;
public:
    paintings(int l, int w, string tech, string mov, string con, int ind, string cr, int y): masterpiece(mov, con, ind, cr, y)
    {
        length = l;
        width = w;
        technique = tech;
        cout << "Creating a instance of class paintings" << endl << endl;
    }
    ~paintings() { cout << "Destroying a instance of class paintings" << endl; }

    void getInfo() const
    {
        masterpiece::getInfo();
        cout << "Length: " << length << " cm" << endl << "Width: " << width
             << " cm" << endl << "Technique: " << technique << endl
             << "Surface: " << (double)((double)length*width)/10000.0 << " square meters" << endl;
    }

    int evaluate(string, string);       //implementation of "pure virtual" (class artifact)
};



class sculptures: public masterpiece{
private:
    int volume;                         //in cubic meters
    string material;
public:
    sculptures(int vol, string mat, string mov, string con, int i, string cr, int y): masterpiece(mov, con, i, cr, y)
    {
        volume = vol;
        material = mat;
        cout << "Creating a instance of class sculptures" << endl << endl;
    }
    ~sculptures() { cout << "Destroying a instance of class sculptures" << endl; }

    void getInfo() const
    {
        masterpiece::getInfo();
        cout << "Volume: " << volume << " cubic meters"
             << endl << "Material: " << material << endl;
    }

    int evaluate(string, string);       //implementation of "pure virtual" (class artifact)
};
