//
// Created by servet on 11.05.2021.
//

#include "player.h"
#include <iostream>
#include "card.h"
using namespace std;

Player::Player(){}

Player::Player(int no, int money){
    this->no = no;
    this->money = money;
}

void Player::withdraw(int amount){
    this->money = (this->money)-amount;
}

void Player::setMoney(int x){
    this->money = x;
}
    

void Player::deposit(int amount){
    this->money = (this->money)+amount;
}