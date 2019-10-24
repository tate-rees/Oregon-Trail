#ifndef MEMBER_H
#define MEMBER_H

#include <string>

using namespace std;

class Member
{
    private:
        string memberName;
        bool alive;
    public:
        //default constructor
        Member();
        
        //setters
        
        //sets the name of the Member to newName
        void setName(string newName);
        //sets life value to false
        void kill();
        
        //getters
        
        //returns memberName
        string getName();
        //returns life value
        bool isAlive();
        
        
};

#endif