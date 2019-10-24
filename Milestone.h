#ifndef MILESTONE_H
#define MILESTONE_H

#include <string>
#include <iostream>

using namespace std;

class Milestone
{
    private:
        string milestoneName;
        int distance;
        int depth;
    public:
        //parametrized constuctor
        Milestone(string name, int dist, int deep);
        
        //returns milestone name
        string getMilestoneName();
        //returns distance
        int getDistance();
        //returns depth
        int getDepth();
};

#endif