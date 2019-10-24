#include "Party.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(){
    //seeds the random number generator
    srand(time(NULL));
    //creates the game's party object
    Party p1 = Party();
    //int to be used for user inputs
    int playerChoice = 0;
    //bool to be used to check if the game is still running
    bool endGame = false;
    
    
    cout << "Welcome to the Oregon Trail!" << endl;
    cout << "You will depart from Independence, Missouri, 2040 miles from Oregon City" << endl;
    cout << "You will need to make it there before November 30, 1847" << endl;
    cout << endl;
    p1.startGame();
    
    cout << "You're now ready for day 1 on the trail" << endl;
    while(playerChoice != 4){
        endGame = p1.gameOver();
        if(endGame == true){
            break;
        }
        p1.statusUpdate();
        
        cout << "Do you want to:" << endl;
        cout << "[1] Rest" << endl;
        cout << "[2] Continue on the trail" << endl;
        cout << "[3] Hunt" << endl;
        cout << "[4] Quit" << endl;
        cin >> playerChoice;
        cout << endl;
        //resting
        if(playerChoice == 1){
            p1.rest();
            //checks if the game should end
            endGame = p1.gameOver();
            if(endGame == true){
                break;
            }
        //continue on trail
        }else if(playerChoice == 2){
            p1.continueOnTrail();
            endGame = p1.gameOver();
            if(endGame == true){
                break;
            }
        //hunt
        }else if(playerChoice == 3){
            p1.hunt();
            endGame = p1.gameOver();
            if(endGame == true){
                break;
            }
        //quit the game
        }else if(playerChoice == 4){
            cout << "Unfortunately, your trip was cut short" << endl;
            cout << endl;
            break;
        }
        endGame = p1.gameOver();
        if(endGame == true){
            break;
        }
        
        //misfortune and raider attacks happen every turn
        if(playerChoice == 1 || playerChoice == 2 || playerChoice == 3){
            p1.misfortune();
            endGame = p1.gameOver();
            if(endGame == true){
                break;
            }
            p1.raiderAttack();
            endGame = p1.gameOver();
            if(endGame == true){
                break;
            }
        }
    }
    cout << "Final results:" << endl;
    //prints final stats
    p1.results();
}