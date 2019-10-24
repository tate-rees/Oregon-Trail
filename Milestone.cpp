#include "Milestone.h"

#include <iostream>
#include <string>

using namespace std;

//parametrized constuctor
Milestone::Milestone(string name, int dist, int deep){
    milestoneName = name;
    distance = dist;
    depth = deep;
}

//returns milestone name
string Milestone::getMilestoneName(){
    return milestoneName;
}
//returns distance
int Milestone::getDistance(){
    return distance;
}
//returns depth
int Milestone::getDepth(){
    return depth;
}
