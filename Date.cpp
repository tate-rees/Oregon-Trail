#include "Date.h"

using namespace std;

//default constructor, sets date to default
Date::Date(){
    months = 3;
    days = 28;
}

//sets the start date
void Date::setStartDate(int month, int day){
    months = month;
    days = day;
}

//adds daysPassed to days
//if the added days are greater than 30/31
//then month increments and leftover days are added to days
void Date::addDays(int numDays){
    int daysInMonth;
    //switch determines value of daysInMonth
    switch(months){
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
            daysInMonth = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            daysInMonth = 30;
            break;
    }
    
    //checks if added days will cause a new month
    if((days + numDays) >  daysInMonth){
        months = months + 1;//goes to next month
        days = days + numDays - daysInMonth;//how many days left over after completing the month
    }else{
        days = days + numDays;
    }
}

//gets the month
int Date::getMonths(){
    return months;
}

//returns the day
int Date::getDays(){
    return days;
}



