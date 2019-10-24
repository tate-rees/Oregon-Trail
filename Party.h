#ifndef PARTY_H
#define PARTY_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "Inventory.h"
#include "Member.h"
#include "Date.h"
#include "Milestone.h"

class Party
{
    private:
        Inventory inventory1;//inventory
        Member members[5];//member array
        Date date1;//date object
        vector<Milestone> milestoneVec;//vector of milestones
        int totalMiles;//total miles travelled
        
    public:
        //default constructor
        Party();
        
        //reads the milestone txt file and parses it into the vector
        //opens the file
        //reads each line into a string
        //creates a milestone object for each milestone
        void readMilestones(string filename);
        
        //calculates the distance to the next milestone
        //returns the distance to the next milestone
        int distToNextMilestone();
        
        //sets the user and their companions' names
        /*
        prompts user for their name
        prompts user for other 4 names
        */
        void setPlayerNames();
        
        //sets the initial conditions of the game
        /*
        1. sets the player's name
        2. sets names of other companions
        3. reads the milestones txt files and parses them into the milestoneVec vector
        4. visit the first store
        5. pick the start date
        */
        void startGame();
        
        //shows status updates
        /**Shows:
         * current date
         * miles travelled
         * distance until next milestone
         * food available
         * bullets available
         * cash available
        */
        void statusUpdate();
        
        //user interaction in the store at each fort
        /**
         * welcome to the store
         * get multiplier by number of miles to indicate which fort, and multiply prices by that
         * player chooses which items, and how many of them
         * update inventory
        */
        void store();
        
        //checks the member array and returns the number of living members
        //returns number of living members
        int getNumLiving();
        
        //if the player chooses to rest
        /*
        1. add 1 to 3 days to the date
        2. eat 3 lbs of food per person per day
        */
        void rest();
        
        //if they encounter a fort
        void fort();
        
        //river milestone encounter
        /*
        1. tell player about the river
        2. ask them if they want to rest or cross
        2a. if they rest, they spend a day, and 3 lbs food per day per person
        2b. if they decide to cross, check if theres a ferry
        2b. i) cross and end the turn if possible
        2b. ii) if ferry is necessary, spend 10 per person per day 
        */
        void river();
        
        //if they choose to continue on the trail
        /*
        1. add 2 weeks to the date (14 days)
        2. 3 lbs per person per day of food
        3. add 70-100 miles to miles travelled
            1. Pull a random number of miles between 70 and 140
            2. Calculate the food that is eaten
            3. Check and see if you will hit a milestone, the do accordingly
        */
        void continueOnTrail();
        
        //if they choose to hunt
        /*
        1. add 1 day to the date
        2. for each animal that they encounter:
            i. ask if they choose to hunt
                if they have less than 10 bullets, they lose them. 
            ii. then they do a puzzle
            iii. if the puzzle is successful
            iiii. generate the amount of food they get and add it, spend bullets
        3. after hunting, player chooses to eat poorly, moderately, well
        */
        void hunt();
        
        //misfortunes
        /*
        1. check chance of misfortune
        2. pick a misfortune
        3. depending on the misfortune, you lose different things. Many exitpoints for the game
        */
        void misfortune();
        
        //calculates the probability of meeting raiders
        //returns true if random number is less than or equal to probability for raiders
        bool chanceOfRaiderAttack();
        
        //raider attacks
        /*
        1. Calc probability of meeting raiders
        2. Choose Run, Attack, Surrender
        3. Apply each choice
        */
        void raiderAttack();
        
        //checks if the game is over
        //returns false when the game is still going
        //returns true if game should end
        bool gameOver();
        
        //writes to a results.txt file
        //get the results stats
        //write them to a file "results.txt"
        void results();
};

#endif