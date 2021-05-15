//
// Created by servet on 11.05.2021.
//

#ifndef BLACKJACK_PLAYER_H
#define BLACKJACK_PLAYER_H
#include <list>

class Player{
    private:
    int money;

    public:
    
    int no;

    Player();
    Player(int no, int money);
    void setPlayerNo(int n);
    void setMoney(int x);
    void withdraw(int amount);
    void deposit(int amount);

    int getPlayerNo(){
        return no;
    }
    int getMoney(){
        return money;
    }


};


#endif //BLACKJACK_PLAYER_H
