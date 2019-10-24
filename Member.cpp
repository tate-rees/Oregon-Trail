#include "Member.h"

#include <string>

using namespace std;

//default constructor
Member::Member(){
    memberName = "";
    alive = true;
}

//setters

//sets the name of the Member to newName
void Member::setName(string newName){
    memberName = newName;
}
//sets life value to false
void Member::kill(){
    alive = false;
}

//getters

//returns memberName
string Member::getName(){
    return memberName;
}
//returns life value
bool Member::isAlive(){
    return alive;
}
