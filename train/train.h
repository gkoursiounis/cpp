class waggon;

class train{
private:
    int totalWaggons;
    int N;
    waggon **trainWaggons;
public:
    train(int, int, int, int);
    ~train();

    void printStatistics() const;

    void operate();
};

