//
// Created by servet on 03.05.2021.
//

#ifndef BLACKJACK_CARD_H
#define BLACKJACK_CARD_H
#include <string>

class Card {
    private:
        char value;
        std::string color;
        int hit_flag;


public:
    Card();
    Card(char value, std::string color, int hit_flag);
    void setVal(char value);
    void setCol(std::string color);
    void setFlag(int x);

    int getFlag(){
        return hit_flag;
    }
    std::string getColor() {
        return color;
    }
    char getVal() {
        return value;
    }


};

#endif //BLACKJACK_CARD_H
