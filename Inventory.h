#ifndef INVENTORY_H
#define INVENTORY_H

using namespace std;

class Inventory
{
    private:
        double money;
        int oxen;
        int bullets;
        int food;
        int medKits;
        int spares;
        
        
    public:
        //default constructor
        Inventory();
        
        //money functions
        
        //returns money value
        double getMoney();
        //reduces money by parameter amount;
        void spendMoney(double amount);
        
        //oxen functions
        
        //returns number of oxen
        int getOxen();
        //reduces number of oxen by 1
        void killOxen();
        //adds specified number to oxen value
        void addOxen(int oxenToAdd);
        
        //bullets functions
        
        //returns number of bullets
        int getBullets();
        //reduces bullets by specified amount
        //if amount is greater than number of bullets, bullets set to 0
        void useBullets(int usedBullets);
        //adds specified amount to bullets
        void addBullets(int bulletsToAdd);
        
        //food functions
        
        //returns amount of food
        int getFood();
        //reduces food by specified amount
        //if amount is greater than amount of food, food set to zero
        void eatFood(int foodToEat);
        //adds specified amount to food
        void addFood(int foodToAdd);
        
        //medKit functions
        
        //returns number of medkits
        int getMedKits();
        //reduces number of medkits by 1
        void useMedKit();
        //adds specified amount to number of medkits
        void addMedKit(int medKitsToAdd);
        
        //spares functions
        
        //returns number of spares
        int getSpares();
        //reduces number of spares by 1
        void useSpare();
        //adds specified amount to number of spares
        void addSpares(int sparesToAdd);
};

#endif