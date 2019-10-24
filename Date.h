#ifndef DATE_H
#define DATE_H

using namespace std;

class Date
{
    private:
        int months;
        int days;
    public:
        //default constructor
        Date();
        
        //sets the start date
        void setStartDate(int month, int day);
        
        //adds daysPassed to days
        //if the added days are greater than 30/31
        //then month increments and leftover days are added to days
        void addDays(int daysPassed);
        
        //gets the month
        int getMonths();
        
        //returns the day
        int getDays();
};

#endif