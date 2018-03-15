#include <ctime>
#include <sstream>
#include "classes.h"

void auction(int, artifacts **, string, string);

int main(int argc, char *argv[])
{
    //arguments

    if(argc != 4)
    {
        cout << "Usage: " << argv[0] << " <N> <movement> <condition>" << endl;
        return 1;
    }

    int N = atoi(argv[1]);

    //some definitions

    artifacts **auctionArtifacts = new artifacts*[N];

    const string movement[] = {"impressionism", "expressionism", "naturalism"};
    const string condition[] = {"bad", "good", "excellent"};
    const string technique[] = {"oil", "aquarelle", "tempera"};
    const string material[] = {"iron", "stone", "wood"};

    srand(time(NULL));
    int index = 0;

    //artifacts creation

    for(int i=0; i<N; i++)
    {
        int paintingOrSculpture = rand()%2;         //if 0 create a painting, else create a sculpture

        int movementSelection = rand()%3;
        int conditionSelection = rand()%3;
        int year = rand()%518 + 1500;               //([0 - 517] + 1500 ) -> 1500 AC to 2017 AC

        stringstream creatorI;                      //creator I (0 to N-1)
        string creator;
        creatorI << "creator" << index;
        creatorI >> creator;

        if(paintingOrSculpture == 0)                //painting creation
        {
            int length = rand()%500 + 1;            //[1, 500] cm
            int width = rand()% 500 + 1;            //[1, 500] cm
            int techniqueSelection = rand()%3;

            auctionArtifacts[i] = new paintings(length, width, technique[techniqueSelection], movement[movementSelection], \
                                                    condition[conditionSelection], index, creator, year);
        }
        else                                        //sculpture creation
        {
            int volume = rand()%10 + 1;             //[1, 10] cubic meters
            int materialSelection = rand()%3;

            auctionArtifacts[i] = new sculptures(volume, material[materialSelection], movement[movementSelection], \
                                                    condition[conditionSelection], index, creator, year);
        }
        index++;
    }

    //auction

    auction(N, auctionArtifacts, argv[2], argv[3]);

    //delete artifacts

    for(int i=0; i<N; i++)
        delete auctionArtifacts[i];
    delete[] auctionArtifacts;

    return 0;
}
