#include "Inventory.h"

using namespace std;

Inventory::Inventory(){
    //double
    money = 1000.00;
    //ints
    oxen = 0;
    bullets = 0;
    food = 0;
    medKits = 0;
    spares = 0;
}

//returns money value
double Inventory::getMoney(){
    return money;  
}
//reduces money by amount
void Inventory::spendMoney(double amount){
    //if the player can spend money;
    if(amount < money){
        money = money - amount;
    }
}

//oxen functions

//returns number of oxen
int Inventory::getOxen(){
    return oxen;
}
//reduces oxen by 1
void Inventory::killOxen(){
    oxen = oxen - 1;
}

void Inventory::addOxen(int oxenToAdd){
    oxen = oxen + oxenToAdd;
}

//bullets functions

//returns number of bullets
int Inventory::getBullets(){
    return bullets;
}
//reduces bullets by specified amount
//if amount is greater than number of bullets, bullets set to 0
void Inventory::useBullets(int usedBullets){
    if(usedBullets >= bullets){
        bullets = 0;
    }else{
        bullets = bullets - usedBullets;
    }
}
//adds specified amount to bullets
void Inventory::addBullets(int bulletsToAdd){
    bullets = bullets + bulletsToAdd;
}

//food functions

//returns amount of food
int Inventory::getFood(){
    return food;
}
//reduces food by specified amount
//if amount is greater than amount of food, food set to zero
void Inventory::eatFood(int foodToEat){
    if(foodToEat >= food){
        food = 0;
    }else{
        food = food - foodToEat;
    }
}
//adds specified amount to food
void Inventory::addFood(int foodToAdd){
    if((foodToAdd + food) > 1000){
        food = 1000;
    }else{
        food = food + foodToAdd;
    }
}

//medKit functions

//returns number of medkits
int Inventory::getMedKits(){
    return medKits;
}
//reduces number of medkits by 1
void Inventory::useMedKit(){
    medKits = medKits - 1;
}
//adds specified amount to number of medkits
void Inventory::addMedKit(int medKitsToAdd){
    medKits = medKits + medKitsToAdd;
}

//spares functions

//returns number of spares
int Inventory::getSpares(){
    return spares;
}
//reduces number of spares by 1
void Inventory::useSpare(){
    spares = spares - 1;
}
//adds specified amount to number of spares
void Inventory::addSpares(int sparesToAdd){
    spares = spares + sparesToAdd;
}