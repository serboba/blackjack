//
// Created by servet on 03.05.2021.
//

#include "card.h"
#include <iostream>
using namespace std;

Card::Card(){

}

Card::Card(char val, std::string col){
    this->value = val;
    this->color = col;
}

void Card::setVal(char val){
    value = val;
}

void Card::setCol(std::string col){
    color = col;
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