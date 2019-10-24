//class files
#include "Party.h"
#include "Date.h"
#include "Inventory.h"
#include "Member.h"
#include "Milestone.h"
//header files
#include <iostream>
#include <fstream>//reading milestone file and writing to results file
#include <string>
#include <vector>
#include <iomanip>//showing prices to 2 dec points
#include <cstdlib>//srand()

using namespace std;

//nonmember functions

//generates a random number between the min and max
int randomNumbers(int min, int max){
    // rand() % (max-min+1) + min
    return (rand() % (max-min+1)) + min;
}

//puzzle for player in raider attacks and hunting
bool puzzle(){
    cout << "To beat the puzzle, guess the random number between 1 and 10" << endl;
    cout << "You have 3 guesses, so good luck" << endl;
    cout << endl;
    int guess;
    int randomNum = randomNumbers(1, 10);
    for(int i = 3; i > 0; i--){
        cout << "You have " << i << " guesses left" << endl;
        cout << "Guess: ";
        cin >> guess;
        if(guess == randomNum){
            cout << "Correct! You solved the puzzle" << endl;
            cout << endl;
            return true;
        }else{
            cout << "Wrong" << endl;
            cout << endl;
        }
    }
    return false;
}


//////////////////////////////////////////
//////////////////////////////////////////


//member functions

//default constructor
Party::Party(){
    totalMiles = 0;
}

//reads the milestone txt file and parses it into the vector
//opens the file
//reads each line into a string
//creates a milestone object for each milestone
void Party::readMilestones(string filename){
    ifstream myfile;
    myfile.open(filename.c_str());
    if(myfile.is_open()){
        //variables that getline reads into
        string mName;
        string stringMiles;
        string stringDepth;
        //goes through the txt file and reads each line, splitting it into its respective parts
        while(getline(myfile, mName, ',')){
            getline(myfile, stringMiles, ',');
            getline(myfile, stringDepth);
            //creates a milestone object
            Milestone milestone1 = Milestone(mName, stoi(stringMiles), stoi(stringDepth));
            //adds milestone to the vector
            milestoneVec.push_back(milestone1);
        }
    }else{
        cout << "file didn't open bro" << endl;;
    }
}

//sets the user and their companions' names
/*
prompts user for their name
prompts user for other 4 names
*/
void Party::setPlayerNames(){
    cout << "Please enter your name" << endl;
    string username;
    getline(cin, username);
    members[0].setName(username);
    cout << members[0].getName() << ", welcome to the Oregon Trail" << endl;
    cout << endl; 
    cout << "Please enter your 4 companions' names: " << endl;
    for(int i = 1; i < 5; i++){
        cout << "Companion number: " << i << endl;
        getline(cin, username);
        members[i].setName(username);
    }
    cout << "Here is your party: " << endl;
    for(int j = 0; j < 5; j++){
        cout << j + 1 << ". " << members[j].getName() << endl;
    }
    cout << endl;
}

//sets the initial conditions of the game
/*
1. sets the player's name
2. sets names of other companions
3. reads the milestones txt files and parses them into the milestoneVec vector
4. visit the first store
5. pick the start date
*/
void Party::startGame(){
    //set the players names
    Party::setPlayerNames();
    //read the milestones file
    Party::readMilestones("milestones.txt");
    
    //set the start date
    cout << "You can depart on 3/28/1847 or choose a date" << endl;
    cout << "[1] Leave on 3/28/1847" << endl;
    cout << "[2] Pick a new departure date" << endl;
    int newDate;
    while(newDate != 1 && newDate != 2){
        cin >> newDate;
    }
    //if they choose to pick a new start date
    if(newDate == 2){
        //picking the month
        cout << "Pick a date between 3/01 and 5/01" << endl;
        int month = 0;
        cout << "Month number: ";
        while(month < 3 || month > 5){
            cin >> month;
        }
        cout << endl;
        
        //picking the day
        int day = 0;
        cout << "Day number: ";
        if(month == 3){
            while(day < 1 || day > 31){
                cin >> day;
            }
        }else if(month == 4){
            while(day < 1 || day > 30){
                cin >> day;
            }
        }else if(month == 5){
            while(day != 1){
                cin >> day;
            }
        }
        //sets the start date to the user input
        date1.setStartDate(month, day);
        cout << endl;
        cout << "You will depart on " << date1.getMonths() << "/" << date1.getDays() << "/1847" << endl;
        cout << endl;
    }else{
        cout << "You will depart on 3/28/1847" << endl;
        cout << endl;
    }
    
    //visiting the first store
    cout << "You will now visit the store" << endl;
    cout << endl;
    cout << "You started with $1200 for the trip to Oregon, and you paid $200" << endl;
    cout << "for the wagon. At the store, you can buy the following items:" << endl;
    int storeChoice;
    //entering the store, storeChoice is the user's selection of which item to get at the store
    while(storeChoice != 5){
        cout << "[1] Oxen - You can spend $100-$200 on oxen. You need them to pull your wagon" << endl;
        cout << "[2] Food - You eat it to get energy. You should know how food works already" << endl;
        cout << "[3] Bullets - You need bullets for hunting and potential raiders" << endl;
        cout << "[4] Miscellaneous Supplies - Med Kits and Spare Parts for emergencies" << endl;
        cout << "[5] Leave the store. Make sure you have oxen and food before you leave!" << endl;
        cout << endl;
        cout << fixed << setprecision(2) << "You have: $" << inventory1.getMoney() << " to spend" << endl;
        cout << "What would you like to do?" << endl;
        cin >> storeChoice;
        //initializing store amounts before the switch statement
        int yokeAmt = 0;
        int foodAmt = 0;
        int boxAmt = 0;
        int spareAmt = 0;
        int medAmt = 0;
        double balance = 0.00;
        int miscChoice = 0;
        switch(storeChoice){
            case 1:
                cout << "Oxen: You must buy between $100 and $200 of oxen" << endl;
                cout << "There are 2 oxen in a yoke, and each yoke is $40" << endl;
                cout << "How many yoke would you like to buy?" << endl;
                while(yokeAmt < 3 || yokeAmt > 5){
                    cin >> yokeAmt;
                }
                balance = yokeAmt * 40.00;
                cout << endl;
                //printing the bill
                cout << fixed << setprecision(2) << "Your bill is $" << balance << endl;
                cout << endl;
                inventory1.addOxen(yokeAmt * 2);
                inventory1.spendMoney(balance);
                break;
            case 2:
                cout << "Food: You should purchase at least 200 pounds of food" << endl;
                cout << "per person. Food is $0.50 per pound" << endl;
                cout << "How many pounds of food would you like to buy?" << endl;
                while(foodAmt <= 0){
                    cin >> foodAmt;
                }
                balance = foodAmt * 0.50;
                cout << endl;
                if(balance >= inventory1.getMoney()){
                    cout << "Not enough money for purchase!" << endl;
                    break;
                }else{
                    cout << fixed << setprecision(2) << "Your bill is $" << balance << endl;
                    cout << endl;
                    inventory1.addFood(foodAmt);
                    inventory1.spendMoney(balance);
                    break;
                }
            case 3:
                cout << "Bullets: You'll use these for hunting if you want them" << endl;
                cout << "They cost $2 for a box of 20 bullets" << endl;
                cout << "How many boxes of bullets would you like to buy" << endl;
                while(boxAmt <= 0){
                    cin >> boxAmt;
                }
                balance = boxAmt * 2.00;
                cout << endl;
                if(balance >= inventory1.getMoney()){
                    cout << "Not enough money for purchase!" << endl;
                    break;
                }else{
                    cout << fixed << setprecision(2) << "Your bill is $" << balance << endl;
                    cout << endl;
                    inventory1.addBullets(boxAmt * 20);
                    inventory1.spendMoney(balance);
                    break;
                }
            case 4:
                cout << "Miscellaneous supplies: You can buy either:" << endl;
                cout << "[1] Medkits - improve chances of survival if someone gets sick" << endl;
                cout << "[2] Spare Parts - might save you if your wagon breaks" << endl;
                while(miscChoice != 1 && miscChoice != 2){
                    cin >> miscChoice;
                }
                if(miscChoice == 1){
                    cout << "Medkits: they cost $25" << endl;
                    cout << "How many medkits would you like?" << endl;
                    while(medAmt <= 0){
                        cin >> medAmt;
                    }
                    balance = medAmt * 25.00;
                    cout << endl;
                    if(balance >= inventory1.getMoney()){
                        cout << "Not enough money for purchase!" << endl;
                        break;
                    }else{
                        cout << fixed << setprecision(2) << "Your bill is $" << balance << endl;
                        inventory1.addMedKit(medAmt);
                        inventory1.spendMoney(balance);
                        break;
                    }
                }else if(miscChoice == 2){
                    cout << "Spare Parts: they cost $20" << endl;
                    cout << "How many spare parts would you like?" << endl;
                    while(spareAmt <= 0){
                        cin >> spareAmt;
                    }
                    balance = spareAmt * 20.00;
                    cout << endl;
                    if(balance >= inventory1.getMoney()){
                        cout << "Not enough money for purchase!" << endl;
                        break;
                    }else{
                        cout << fixed << setprecision(2) << "Your bill is $" << balance << endl;
                        inventory1.addSpares(spareAmt);
                        inventory1.spendMoney(balance);
                        break;
                    }
                }
            case 5:
                cout << "Thanks for visiting the store!" << endl;
                cout << "You will have other opportunities to visit the store. However, supplies are more" << endl;
                cout << "expensive at future forts. You will also be able to hunt for food on your journey" << endl;
                cout << endl;
                break;
        }
    }
}

//calculates the distance to the next milestone
//returns the distance to the next milestone
int Party::distToNextMilestone(){
    int distanceAway;
    if(milestoneVec.size() > 0){
        int dist = milestoneVec[0].getDistance();
        distanceAway = dist - totalMiles;
        return distanceAway;
    }else{
        distanceAway = 2040 - totalMiles;
        return distanceAway;
    }
}
        
//shows status updates
/**Shows:
* current date
* miles travelled
* distance until next milestone
* food available
* bullets available
* cash available
*/
void Party::statusUpdate(){
    cout << "Current date: " << date1.getMonths() << "/" << date1.getDays() << "/1847" << endl;
    cout << "Miles travelled: " << totalMiles << " miles" << endl;
    cout << "Distance to next milestone: " << Party::distToNextMilestone() << " miles" << endl;
    cout << "Food available: " << inventory1.getFood() << " lbs." << endl;
    cout << "Bullets available: " << inventory1.getBullets() << " bullets" << endl;
    cout << fixed << setprecision(2) << "Cash available: $" << inventory1.getMoney() << endl;
    //cout << "Spares " << inventory1.getSpares() << endl;
    cout << endl;
}

//user interaction in the store at each fort
/**
 * welcome to the store
 * get multiplier by number of miles to indicate which fort, and multiply prices by that
 * player chooses which items, and how many of them
 * update inventory
*/
void Party::store(){
    //to set the prices for each fort
    double priceMultiplier = -1.0;
    switch(totalMiles){
        case 304://fort kearney
            priceMultiplier = 1.25;
            break;
        case 640://fort laramie
            priceMultiplier = 1.5;
            break;
        case 989://fort bridger
            priceMultiplier = 1.75;
            break;
        case 1395://fort hall
            priceMultiplier = 2.00;
            break;
        case 1648://fort boise
            priceMultiplier = 2.25;
            break;
        case 1863://fort walla walla
            priceMultiplier = 2.50;
            break;
    }
    cout << endl;
    //store interaction
    cout << "Welcome to the store!" << endl;
    cout << "Here you can purchase all the things you need" << endl;
    cout << "Select from the following items:" << endl;
    int storeChoice;
    while(storeChoice != 5){
        cout << "[1] Oxen - Oxen pull your wagon, so make sure you have enough" << endl;
        cout << "[2] Food - You eat it to get energy. Food, it's pretty simple" << endl;
        cout << "[3] Bullets - You use bullets for hunting and defending against raiders" << endl;
        cout << "[4] Miscellaneous Supplies - Med Kits and Spare Parts for emergencies" << endl;
        cout << "[5] Leave the store" << endl;
        cout << endl;
        cout << fixed << setprecision(2) << "You have: $" << inventory1.getMoney() << " to spend" << endl;
        cout << "What would you like to do?" << endl;
        cin >> storeChoice;
        cout << endl;
        int cart = -1;
        double balance = 0.00;
        int miscChoice = 0;
        switch(storeChoice){
            case 1:
                cout << "Oxen are $" << priceMultiplier*40.0 << " per yoke" << endl;
                cout << "and there are 2 oxen per yoke. How many yokes would you like?" << endl;
                while(cart < 0){
                    cin >> cart;
                }
                cout << endl;
                balance = cart * 40.00 * priceMultiplier;
                if(balance >= inventory1.getMoney()){
                    cout << "You don't have enough money for this purchase." << endl;
                    break;
                }else{
                    cout << fixed << setprecision(2) << "Your total is $" << balance << endl;
                    inventory1.spendMoney(balance);
                    inventory1.addOxen(cart * 2);
                    break;
                }
            case 2:
                cout << "Food is $" << priceMultiplier*0.50 << " per pound" << endl;
                cout << "How many pounds of food would you like?" << endl;
                while(cart < 0){
                    cin >> cart;
                }
                cout << endl;
                balance = cart * 0.50 * priceMultiplier;
                if(balance >= inventory1.getMoney()){
                    cout << "You don't have enough money for this purchase." << endl;
                    break;
                }else{
                    cout << fixed << setprecision(2) << "Your total is $" << balance << endl;
                    inventory1.spendMoney(balance);
                    inventory1.addFood(cart);
                    break;
                }
            case 3:
                cout << "Bullets are $" << priceMultiplier*2.0 << " per box and there" << endl;
                cout << "are 20 bullets per box. How many boxes would you like?" << endl;
                while(cart < 0){
                    cin >> cart;
                }
                cout << endl;
                balance = cart * 2.00 * priceMultiplier;
                if(balance >= inventory1.getMoney()){
                    cout << "You don't have enough money for this purchase." << endl;
                    break;
                }else{
                    cout << fixed << setprecision(2) << "Your total is $" << balance << endl;
                    inventory1.spendMoney(balance);
                    inventory1.addBullets(cart * 20);
                    break;
                }
            case 4:
                cout << "Miscellaneous supplies, pick:" << endl;
                cout << "[1] Med Kits" << endl;
                cout << "[2] Spare Parts" << endl;
                while(miscChoice != 1 && miscChoice != 2){
                    cin >> miscChoice;
                }
                if(miscChoice == 1){
                    cout << "Med Kits are $" << priceMultiplier*25.00 << endl;
                    cout << "How many would you like?" << endl;
                    while(cart < 0){
                        cin >> cart;
                    }
                    cout << endl;
                    balance = cart * 25.00 * priceMultiplier;
                    if(balance >= inventory1.getMoney()){
                        cout << "You don't have enough money for this purchase." << endl;
                        break;
                    }else{
                        cout << fixed << setprecision(2) << "Your total is $" << balance << endl;
                        inventory1.spendMoney(balance);
                        inventory1.addMedKit(cart);
                        break;
                    }
                }else if(miscChoice == 2){
                    cout << "Spare Parts are $" << priceMultiplier*20.00 << endl;
                    cout << "How many would you like?" << endl;
                    while(cart < 0){
                        cin >> cart;
                    }
                    cout << endl;
                    balance = cart * 20.00 * priceMultiplier;
                    if(balance >= inventory1.getMoney()){
                        cout << "You don't have enough money for this purchase." << endl;
                        break;
                    }else{
                        cout << fixed << setprecision(2) << "Your total is $" << balance << endl;
                        inventory1.spendMoney(balance);
                        inventory1.addSpares(cart);
                        break;
                    }
                }
            case 5:
                cout << "Thanks for visiting the store, come again!" << endl;
                break;
        }
    }
}

//checks the member array and returns the number of living members
//returns number of living members
int Party::getNumLiving(){
    int counter = 0;
    for(int i = 0; i < 5; i++){
        if(members[i].isAlive() == true){
            counter++;
        }
    }
    return counter;
}

//fort milestone encounter
void Party::fort(){
    cout << "At " << milestoneVec[0].getMilestoneName() << " you can rest or visit the store" << endl;
    
    //user's choice
    int fortChoice = 0;
    while(fortChoice != 3){
        //prompt user
        cout << "Would you like to:" << endl;
        cout << "[1] Rest" << endl;
        cout << "[2] Visit the store" << endl;
        cout << "[3] Continue on the journey" << endl;
        cin >> fortChoice;
        cout << endl;
        
        //choose to rest
        if(fortChoice == 1){
            int foodEaten;
            int numLiving = Party::getNumLiving();
            foodEaten = numLiving * 3;
            cout << "You choose to rest for a day" << endl;
            cout << "Your party ate " << foodEaten << " pounds of food" << endl;
            cout << endl;
            date1.addDays(1);
            inventory1.eatFood(foodEaten);
        //choose to visit the store
        }else if(fortChoice == 2){
            cout << "You choose to go to the store" << endl;
            cout << endl;
            cout << "STORE" << endl;
            cout << "---------------------" << endl;
            Party::store();
        //choose to leave the fort
        }else if(fortChoice == 3){
            cout << "You choose to leave " << milestoneVec[0].getMilestoneName() << endl;
            cout << endl;
        }
    }
}

//river milestone encounter
/*
1. tell player about the river
2. ask them if they want to rest or cross
2a. if they rest, they spend a day, and 3 lbs food per day per person
2b. if they decide to cross, check if theres a ferry
2b. i) cross and end the turn if possible
2b. ii) if ferry is necessary, spend 10 per person per day 
*/
void Party::river(){
    cout << milestoneVec[0].getMilestoneName() << " is " << milestoneVec[0].getDepth() << " feet deep" << endl;

    //for user's choice
    int riverChoice = 0;
    while(riverChoice != 2){
        //prompt user about the river milestone
        cout << "Would you like to:" << endl;
        cout << "[1] Rest" << endl;
        cout << "[2] Cross" << endl;
        cin >> riverChoice;
        cout << endl;
        
        //choose to rest
        if(riverChoice == 1){
            int foodEaten;
            int numLiving = Party::getNumLiving();
            foodEaten = numLiving * 3;
            cout << "You choose to rest for a day" << endl;
            cout << "Your party ate " << foodEaten << " pounds of food" << endl;
            cout << endl;
            date1.addDays(1);
            inventory1.eatFood(foodEaten);
        }else if(riverChoice == 2){
            cout << "You choose to cross the river" << endl;
            cout << endl;
            if(milestoneVec[0].getDepth() > 3){
                int numLiving = Party::getNumLiving();
                double costOfFerry = numLiving * 10.00;
                cout << "The river was deep enough to require a ferry" << endl;
                cout << fixed << setprecision(2) << "The ferry cost $" << costOfFerry << endl;
                cout << endl;
                //spend money on the ferry
                inventory1.spendMoney(costOfFerry);
            }
        }
    }
}

//if the player chooses to continue
/*
1. Pull a random number of miles between 70 and 140
2. Calculate the food that is eaten
3. Check and see if you will hit a milestone, the do accordingly
*/
void Party::continueOnTrail(){
    int randMiles = randomNumbers(70, 140);
    int distToMilestone = Party::distToNextMilestone();
    int numLiving = Party::getNumLiving();
    int foodEaten = numLiving * 3 * 14;
    if(randMiles < distToMilestone){
        cout << "You travelled " << randMiles << " miles in two weeks" << endl;
        cout << endl;
        totalMiles = totalMiles + randMiles;
        date1.addDays(14);
        inventory1.eatFood(foodEaten);
    }else{
        cout << "You were prepared to travel " << randMiles << " miles but arrived at:" << endl;
        cout << milestoneVec[0].getMilestoneName() << endl;
        cout << endl;
        totalMiles = totalMiles + distToMilestone;
        date1.addDays(14);
        inventory1.eatFood(foodEaten);
        if(milestoneVec[0].getDepth() < 0){
            Party::fort();
            milestoneVec.erase(milestoneVec.begin() + 0);
        }else{
            Party::river();
            milestoneVec.erase(milestoneVec.begin() + 0);
        }
    }
}

//if the player chooses to rest
/*
1. add 1 to 3 days to the date
2. eat 3 lbs of food per person per day
*/
void Party::rest(){
    //calculate the number of days rested
    int daysRested;
    daysRested = randomNumbers(1, 3);
    cout << "You rested for " << daysRested << " days" << endl;
    //calculate number of eating members
    int numLiving;
    numLiving = Party::getNumLiving();
    //calculate food eaten
    int foodEaten;
    foodEaten = numLiving * daysRested * 3;
    cout << "You also ate " << foodEaten << " pounds of food" << endl;
    //spend days and food
    inventory1.eatFood(foodEaten);
    date1.addDays(daysRested);
    cout << endl;
}

//if they choose to hunt
/*
1. add 1 day to the date
2. for each animal that they encounter:
i. ask if they choose to hunt. if they have less than 10 bullets, they lose them. 
ii. then they do a puzzle
iii. if the puzzle is successful
iiii. generate the amount of food they get and add it, spend bullets
3. after hunting, player chooses to eat poorly, moderately, well
*/
void Party::hunt(){
    //add a day for the turn
    date1.addDays(1);
    cout << "You went out hunting" << endl;
    cout << endl;
    //variables to be used for each of the hunting probabilities
    int randHunt;
    int willHunt;
    bool puzzleSuccess;
    int foodGained;
    int totalFoodInHunt = 0;
    
    //the 5 potential animal encounters
    
    //for rabbits
    randHunt = randomNumbers(1, 100);
    if(randHunt <= 50){//did encounter
        willHunt = 0;
        cout << "You encountered a rabbit" << endl;
        cout << endl;
        while(willHunt != 1 && willHunt != 2){
            cout << "Would you like to hunt the rabbit?" << endl;
            cout << "[1] Yes" << endl;
            cout << "[2] No" << endl;
            cin >> willHunt;
            cout << endl;
            
            //player chooses to hunt
            if(willHunt == 1){
                if(inventory1.getBullets() < 10){
                    cout << "The hunt was unsuccessful. Bring more bullets next time" << endl;
                }else{
                    cout << "Solve the puzzle to have a succesful hunt" << endl;
                    cout << endl;
                    puzzleSuccess = puzzle();
                    inventory1.useBullets(10);
                    if(puzzleSuccess == true){//complete the puzzle 
                        cout << "Hunt was successful!" << endl;
                        foodGained = 2;
                        totalFoodInHunt = totalFoodInHunt + foodGained;
                        inventory1.addFood(foodGained);
                        cout << "You gained " << foodGained << " lbs of food" << endl;
                    }else{//didn't complete the puzzle
                        cout << "Hunt was unsuccessful. Better luck next time" << endl;
                    }
                }
            }
        }
    }
    cout << endl;
    cout << endl;
    
    //for fox
    randHunt = randomNumbers(1, 100);
    if(randHunt <= 25){//did encounter
        willHunt = 0;
        cout << "You encountered a fox" << endl;
        cout << endl;
        while(willHunt != 1 && willHunt != 2){
            cout << "Would you like to hunt the fox?" << endl;
            cout << "[1] Yes" << endl;
            cout << "[2] No" << endl;
            cin >> willHunt;
            cout << endl;
            
            //player chooses to hunt
            if(willHunt == 1){
                if(inventory1.getBullets() < 10){
                    cout << "The hunt was unsuccessful. Bring more bullets next time" << endl;
                }else{
                    cout << "Solve the puzzle to have a succesful hunt" << endl;
                    cout << endl;
                    puzzleSuccess = puzzle();
                    inventory1.useBullets(8);
                    if(puzzleSuccess == true){//complete the puzzle 
                        cout << "Hunt was successful!" << endl;
                        foodGained = 5;
                        totalFoodInHunt = totalFoodInHunt + foodGained;
                        inventory1.addFood(foodGained);
                        cout << "You gained " << foodGained << " lbs of food" << endl;
                    }else{//didn't complete the puzzle
                        cout << "Hunt was unsuccessful. Better luck next time" << endl;
                    }
                }
            }
        }
    }
    cout << endl;
    cout << endl;
    
    //for deer
    randHunt = randomNumbers(1, 100);
    if(randHunt <= 15){//did encounter
        willHunt = 0;
        cout << "You encountered a deer" << endl;
        cout << endl;
        while(willHunt != 1 && willHunt != 2){
            cout << "Would you like to hunt the deer?" << endl;
            cout << "[1] Yes" << endl;
            cout << "[2] No" << endl;
            cin >> willHunt;
            cout << endl;
            
            //player chooses to hunt
            if(willHunt == 1){
                if(inventory1.getBullets() < 10){
                    cout << "The hunt was unsuccessful. Bring more bullets next time" << endl;
                }else{
                    cout << "Solve the puzzle to have a succesful hunt" << endl;
                    cout << endl;
                    puzzleSuccess = puzzle();
                    inventory1.useBullets(5);
                    if(puzzleSuccess == true){//complete the puzzle 
                        cout << "Hunt was successful!" << endl;
                        foodGained = randomNumbers(30,55);
                        totalFoodInHunt = totalFoodInHunt + foodGained;
                        inventory1.addFood(foodGained);
                        cout << "You gained " << foodGained << " lbs of food" << endl;
                    }else{//didn't complete the puzzle
                        cout << "Hunt was unsuccessful. Better luck next time" << endl;
                    }
                }
            }
        }
    }
    cout << endl;
    cout << endl;
    
    //for bear
    randHunt = randomNumbers(1, 100);
    if(randHunt <= 7){//did encounter
        willHunt = 0;
        cout << "You encountered a bear" << endl;
        cout << endl;
        while(willHunt != 1 && willHunt != 2){
            cout << "Would you like to hunt the bear?" << endl;
            cout << "[1] Yes" << endl;
            cout << "[2] No" << endl;
            cin >> willHunt;
            cout << endl;
            
            //player chooses to hunt
            if(willHunt == 1){
                if(inventory1.getBullets() < 10){
                    cout << "The hunt was unsuccessful. Bring more bullets next time" << endl;
                }else{
                    cout << "Solve the puzzle to have a succesful hunt" << endl;
                    cout << endl;
                    puzzleSuccess = puzzle();
                    inventory1.useBullets(10);
                    if(puzzleSuccess == true){//complete the puzzle 
                        cout << "Hunt was successful!" << endl;
                        foodGained = randomNumbers(100,350);
                        totalFoodInHunt = totalFoodInHunt + foodGained;
                        inventory1.addFood(foodGained);
                        cout << "You gained " << foodGained << " lbs of food" << endl;
                    }else{//didn't complete the puzzle
                        cout << "Hunt was unsuccessful. Better luck next time" << endl;
                    }
                }
            }
        }
    }
    cout << endl;
    cout << endl;
    
    //for moose
    randHunt = randomNumbers(1, 100);
    if(randHunt <= 5){//did encounter
        willHunt = 0;
        cout << "You encountered a moose" << endl;
        cout << endl;
        while(willHunt != 1 && willHunt != 2){
            cout << "Would you like to hunt the moose?" << endl;
            cout << "[1] Yes" << endl;
            cout << "[2] No" << endl;
            cin >> willHunt;
            cout << endl;
            
            //player chooses to hunt
            if(willHunt == 1){
                if(inventory1.getBullets() < 10){
                    cout << "The hunt was unsuccessful. Bring more bullets next time" << endl;
                    cout << endl;
                }else{
                    cout << "Solve the puzzle to have a succesful hunt" << endl;
                    cout << endl;
                    puzzleSuccess = puzzle();
                    inventory1.useBullets(12);
                    if(puzzleSuccess == true){//complete the puzzle 
                        cout << "Hunt was successful!" << endl;
                        foodGained = randomNumbers(300,600);
                        totalFoodInHunt = totalFoodInHunt + foodGained;
                        inventory1.addFood(foodGained);
                        cout << "You gained " << foodGained << " lbs of food" << endl;
                    }else{//didn't complete the puzzle
                        cout << "Hunt was unsuccessful. Better luck next time" << endl;
                    }
                }
            }
        }
    }
    cout << endl;
    cout << endl;
    
    //they party chooses how well to eat after hunting
    cout << "After hunting, your party can choose how well to eat" << endl;
    //player chooses how well to eat
    int numLiving = Party::getNumLiving();
    int foodEaten;
    int eatChoice = 0;
    while(eatChoice != 1 && eatChoice != 2 && eatChoice != 3){
        cout << "How well would you like to eat?" << endl;
        cout << endl;
        cout << "[1] Poor - 2 lbs per person" << endl;
        cout << "[2] Moderately - 3 lbs per person" << endl;
        cout << "[3] Well - 5 lbs per person" << endl;
        cin >> eatChoice;
        cout << endl;
        
        //if they choose to eat poor
        if(eatChoice == 1){
            foodEaten = numLiving * 2;
            inventory1.eatFood(foodEaten);
            cout << "Your party ate poorly today" << endl;
            cout << endl;
        //if they choose to eat moderately
        }else if(eatChoice == 2){
            foodEaten = numLiving * 3;
            inventory1.eatFood(foodEaten);
            cout << "Your party ate poorly today" << endl;
            cout << endl;
        //if they choose to eat well
        }else if(eatChoice == 3){
            foodEaten = numLiving * 5;
            inventory1.eatFood(foodEaten);
            cout << "Your party ate well today" << endl;
            cout << endl;
        }
    }
    
    int netFood = totalFoodInHunt + inventory1.getFood() - foodEaten;
    if(netFood > 1000){
        cout << "Your wagon can only hold 1000 lbs of food, so some had to be left behind" << endl;
    }
    
}

//misfortunes
/*
1. check chance of misfortune
2. pick a misfortune
3. depending on the misfortune, you lose different things. Many exitpoints for the game
*/
void Party::misfortune(){
    //figure out the chance of a misfortune
    int misfortuneChance = randomNumbers(1, 10);
    int misfortuneType = randomNumbers(1, 3);
    //different disasters that could happen for each misfortune
    string diseases[6] = {"typhoid","cholera","diarrhea","measles","dysentery","a fever"};
    string brokenParts[3] = {"wheels","axles","tongues"};
    //if the misfortune occurs
    if(misfortuneChance <= 4){
        cout << "Oh no!" << endl;
        cout << endl;
        //someone gets sick
        if(misfortuneType == 1){
            //will hold the indexes of the member array of the living members
            vector<int> livingMembers;
            //puts the indexes of the living party members into a vector
            for(int i = 0; i < 5; i++){
                if(members[i].isAlive() == true){
                    livingMembers.push_back(i);
                }
            }
            //picks a random member out of the living members vector
            int sickIndex = livingMembers[randomNumbers(0, (livingMembers.size() - 1))];
            //picks a sickness
            int diseaseIndex = randomNumbers(0, 5);
            
            cout << members[sickIndex].getName() << " has " << diseases[diseaseIndex] << endl;
            cout << endl;
            int deathChance = randomNumbers(1, 10);
            //if they have a med kit
            if(inventory1.getMedKits() > 0){
                cout << "A med kit was used" << endl;
                inventory1.useMedKit();
                cout << endl;
                if(deathChance <= 5){
                    if(sickIndex != 0){
                        cout << members[sickIndex].getName() << " died of " << diseases[diseaseIndex] << endl;
                        cout << endl;
                    }else{
                        cout << "You died of " << diseases[diseaseIndex] << endl;
                        cout << endl;
                    }
                    members[sickIndex].kill();
                }else{
                    cout << members[sickIndex].getName() << " survived!" << endl;
                    cout << endl;
                }
            //no med kits
            }else{
                cout << "You can give " << members[sickIndex].getName() << " time to rest, or you can" << endl;
                cout << "choose to press on. What would you like to do?" << endl;
                //choose to rest or press on
                int sickChoice = 0;
                while(sickChoice != 1 && sickChoice != 2){
                    cout << "[1] Rest" << endl;
                    cout << "[2] Press On!" << endl;
                    cin >> sickChoice;
                    cout << endl;
                    
                    //choose to rest
                    if(sickChoice == 1){
                        date1.addDays(3);
                        cout << "You rested for three days" << endl;
                        cout << endl;
                        if(deathChance <= 3){
                            if(sickIndex != 0){
                                cout << members[sickIndex].getName() << " died of " << diseases[diseaseIndex] << endl;
                                cout << endl;
                            }else{
                                cout << "You died of " << diseases[diseaseIndex] << endl;
                                cout << endl;
                            }
                            members[sickIndex].kill();
                        }else{
                            cout << members[sickIndex].getName() << " survived!" << endl;
                            cout << endl;
                        }
                        
                    //choose to press on
                    }else if(sickChoice == 2){
                        cout << "You decided to press on" << endl;
                        cout << endl;
                        //if they die
                        if(deathChance <= 7){
                            //not the leader dying
                            if(sickIndex != 0){
                                cout << members[sickIndex].getName() << " died of " << diseases[diseaseIndex] << endl;
                                cout << endl;
                            //leader dying
                            }else{
                                cout << "You died of " << diseases[diseaseIndex] << endl;
                                cout << endl;
                            }
                            members[sickIndex].kill();
                        //don't die
                        }else{
                            cout << members[sickIndex].getName() << " survived!" << endl;
                            cout << endl;
                        }
                    }
                }
            }
        //oxen dies
        }else if(misfortuneType == 2){
            inventory1.killOxen();
            cout << "One of the oxen has died" << endl;
            if(inventory1.getOxen() > 1){
                cout << "You have " << inventory1.getOxen() << " left" << endl;
                cout << endl;
            }
            
        //part of the wagon broke
        }else if(misfortuneType == 3){
            int brokeIndex = randomNumbers(0,2);
            cout << "One of your " << brokenParts[brokeIndex] << " is broken" << endl;
            inventory1.useSpare();
            if(inventory1.getSpares() > 0){
                cout << "You used one of your spare parts to fix it" << endl;
                cout << endl;
            }else{
                cout << "You didn't have any spare parts, so you are unable to continue your journey" << endl;
                cout << endl;
            }
        }
    }
}

//calculates the probability of meeting raiders
//returns true if random number is less than or equal to probability for raiders
bool Party::chanceOfRaiderAttack(){
    double raiderProbability;
    double x = ((totalMiles/100.00)-4)*((totalMiles/100.00)-4);
    raiderProbability = ((x + 72.) / (x + 12.)) - 1;
    raiderProbability = raiderProbability * 10;
    int raiderChance = randomNumbers(0,99);
    if(raiderChance <= raiderProbability){
        return true;
    }else{
        return false;
    }
}

//raider attacks
/*
1. Calc probability of meeting raiders
2. Choose Run, Attack, Surrender
3. Apply each choice
*/
void Party::raiderAttack(){
    bool raiders = Party::chanceOfRaiderAttack();
    //if a raider attack does happen
    if(raiders == true){
        cout << "Raiders ahead! They look hostile" << endl;
        
        int raiderChoice = 0;
        while(raiderChoice != 1 && raiderChoice != 2 && raiderChoice != 3){
            cout << "You can:" << endl;
            cout << "[1] Run" << endl;
            cout << "[2] Attack" << endl;
            cout << "[3] Surrender" << endl;
            cin >> raiderChoice;
            cout << endl;
            
            //if they choose to run
            if(raiderChoice == 1){
                cout << "You escaped with your lives, but you left some things behind" << endl;
                cout << endl;
                inventory1.killOxen();
                inventory1.eatFood(10);
                
            //they choose to attack
            }else if(raiderChoice == 2){
                cout << "To beat the raiders, you must pass a puzzle" << endl;
                bool puzzleSuccess = puzzle();
                //if they win the puzzle
                if(puzzleSuccess == true){
                    cout << "You beat the raiders" << endl;
                    cout << endl;
                    inventory1.addFood(50);
                    inventory1.addBullets(50);
                //they don't win the puzzle
                }else{
                    cout << "The raiders won" << endl;
                    cout << endl;
                    double moneyLost = inventory1.getMoney() * 0.25;
                    inventory1.spendMoney(moneyLost);
                    inventory1.useBullets(50);
                }
            //if they choose to surrender
            }else if(raiderChoice == 3){
                cout << "You surrendered, and the raiders took some things" << endl;
                cout << endl;
                double cashLost = inventory1.getMoney() * 0.25;
                inventory1.spendMoney(cashLost);
            }
        }
    }
}

//checks if the game is over
//returns false when the game is still going
//returns true if the game should end
bool Party::gameOver(){
    if(totalMiles >= 2040){
        totalMiles = 2040;
        cout << "You made it to Oregon City! It was a long journey, but you made it 2040 miles here" << endl;
        return true;
    }else if(inventory1.getFood() <= 0){
        cout << "You ran out of food, so you were unable to continue your journey" << endl;
        return true;
    }else if(inventory1.getOxen() <= 0){
        cout << "All of your oxen are dead, so you have to halt your journey to Oregon" << endl;
        return true;
    }else if(inventory1.getSpares() < 0){
        return true;
    }else if(members[0].isAlive() == false){
        return true;
    }else if(date1.getMonths() > 11){
        cout << "You couldn't make it by winter, so everyone froze to death" << endl;
        return true;
    }else{
        return false;
    }
}

//writes to a results.txt file
//get the results stats
//write them to a file "results.txt"
void Party::results(){
    cout << endl;
    
    
    ofstream myfile;
    myfile.open("results.txt");
    if(myfile.is_open()){
        
        myfile << "Leader: " << members[0].getName() << endl;
        cout << "Leader: " << members[0].getName() << endl;
        
        myfile << "Miles travelled: " << totalMiles << endl;
        cout << "Miles travelled: " << totalMiles << endl;
        
        myfile << "Last day on trail: " << date1.getMonths() << "/" << date1.getDays() << "/1847" << endl;
        cout << "Last day on trail: " << date1.getMonths() << "/" << date1.getDays() << "/1847" << endl;
        
        myfile << "Food remaining: " << inventory1.getFood() << endl;
        cout << "Food remaining: " << inventory1.getFood() << endl;
        
        myfile << fixed << setprecision(2) << "Cash remaining: $" << inventory1.getMoney() << endl;
        cout << fixed << setprecision(2) << "Cash remaining: $" << inventory1.getMoney() << endl;
        
    }else{
        cout << "couldn't write a results file" << endl;
    }
}

