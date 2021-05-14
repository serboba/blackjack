//
// Created by servet on 11.05.2021.
//

#include "player.h"
#include <iostream>
#include "card.h"
using namespace std;

class Player{
    int no;
    int money;

    public:

    void setPlayerNo(int n){
        no = n;
    }
    int getPlayerNo(){
        return no;
    }

    void setMoney(int x){
        money = x;
    }
    int getMoney(){
        return money;
    }


};