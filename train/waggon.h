class linkedList;

class waggon{
private:
    int maxCapacity;
    int currentPassengers;
    int isChecked;              //1 if the waggon is going to be checked, else 0
    int offenders;              //TOTAL offenders
    int avoidedCheck;           //TOTAL number of passengers avoided the ticket check
    int finesCollected;
    int finePrice;
    linkedList *waggonPassengers;
public:
    waggon(int, int);
    ~waggon();

    void inStation(int, int);
    void betweenStations();
    void boarding();                                //board random passengers
    void disembarkation(const int&, const int&);    //disembark random passengers
    void offendersDisembarkation();                 //disembark offenders

    int getFinesCollected() const { return finesCollected; }
    void printStatistics() const;
};
