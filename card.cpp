//
// Created by servet on 03.05.2021.
//

#include "card.h"
#include <iostream>
using namespace std;

Card::Card(){

}

Card::Card(char val, std::string col, int hit_flag){
    this->value = val;
    this->color = col;
    this->hit_flag = hit_flag;
}

void Card::setVal(char val){
    value = val;
}

void Card::setCol(std::string col){
    color = col;
}

void Card::setFlag(int x){
    this->hit_flag = x;
}
/* cols = 'spades', 'diamonds', 'hearts', 'clubs'
        suits_symbols = '♠', '♦', '♥', '♣' */
        /* 
        HIDDEN_CARD = """\
┌─────────┐
│░░░░░░░░░│
│░░░░░░░░░│
│░░░░░░░░░│
│░░░░░░░░░│
│░░░░░░░░░│
│░░░░░░░░░│
│░░░░░░░░░│
└─────────┘
*/
/*
┌─────────┐
│{}       │
│         │
│         │
│    {}   │
│         │
│         │
│       {}│
└─────────┘
*/