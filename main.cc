#include <iostream>
#include "chess.h"

using namespace std;

int main(int argc, char **argv)
{
    bool useDisplay = true;
    if (argc == 2)
    {
        string arg = argv[1];
        if (arg == "--no-display")
        {
            useDisplay = false;
        }   
    }
    Chess c;
    c.start(useDisplay);

    return 0;
}