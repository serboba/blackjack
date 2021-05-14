#include <iostream>
#include "card.h"
#include "player.cpp"
#include "printer.h"
#include <stack>
#include <list>
#include <time.h>
#include <stdlib.h>

using namespace std;
Printer print;
    

Card * initDeck(){
    Card *deck = new Card[52];
    string colors [4] = {"hearts" , "diamonds", "clubs", "spades"};
    const char cardtypes[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    for(int j = 0; j<4; j++) {
        for (int i = 0; i < 13; i++) {
            Card c(cardtypes[i],colors[j]);
            //c.setVal(cardtypes[i]);
            //c.setCol(colors[j]);
            deck[(j*13)+i] = c;
        }
    }
    /*
    for(Card c : deck){
        cout << c.getVal() + c.getColor() <<endl;
    }
    */
  return deck;
}

int get_hand_value(std::list<Card> hand){
    int value = 0;
    int ace_flag = 0;
    int list_size = hand.size();

    for (int i = 0; i<list_size; i++){
        //cout <<"my val : "  << value << endl;
        Card hob = hand.front();
        hand.pop_front();
        //cout << "current hoe:" <<hob.getVal() << endl;
        if (hob.getVal() == 'A') {
            if (value < 11) {
                value += 11;
                ace_flag =1;
            } else {
                value += 1;
            }
            continue;
        }
        if (hob.getVal() == 'J' || (hob.getVal() == 'Q') || (hob.getVal() == 'K') || hob.getVal()=='T'){
            value += 10;
        }else{
            int keko = (hob.getVal()-48);
            value += keko;
            if(value >21 && ace_flag == 1){
                value -= 10;
            }
        }
    }
    //cout<< "finito: " << value <<endl;
    return value;
}

int validate_hand(int value){
    if(value>21){
        cout << "U BUST" <<endl;
        return 0;
    }else if(value ==21){
        cout << "BLACKJACK?? STOP" << endl;
        return 2;
    }else{
        cout << "U CAN HIT" << endl;
        return 1;
    }
}

void hit_card(Card *deck, std::list<Card> &hand){
    int random = rand()%51 +1;
    
    while(1){
        random = rand()%51 + 1;
        if (Card(deck[random]).getVal() != -1){
            cout <<"U TOOK: " <<Card(deck[random]).getVal() << Card(deck[random]).getColor() << endl;
            hand.push_back(Card(deck[random]));
            Card(deck[random]).setVal(-1);
            break;
        }
    }
}


void play_player(Card *deck, std::list<Card> &hand){
    char req;
    if(get_hand_value(hand) == 21){
        cout << "BLACKJACK U WON." <<  endl;
        return;
    }
    int flag = 0;
    while(validate_hand(get_hand_value(hand))){
        cout << "U got now : " << get_hand_value(hand) << endl;
        cout << "Type 'h' for hit, 'd' for double, 's' for stand" << endl;
        cin >> req;
        switch (req)
        {
        case 'h':
            hit_card(deck, hand);
            break;
        case 'd':
            // hit break double chips?
            hit_card(deck,hand);
            flag = 1;
            break;
        case 's':
            flag = 1;
            break;
        default:
            
            break;
        }
        print.get_card_print(hand);
        cout << "U got now : " << get_hand_value(hand) << endl;
        if (flag || get_hand_value(hand) == 21){
            return;
        }
    }
     
}

int check_tie(int player_value, int dealer_value){

    if ((player_value == dealer_value) && dealer_value >=17){
        return 1;
    }else{
        return 0;
    }

}

void play_dealer(Card * deck, std::list<Card> &hand, int player_value){
    int dealer_value = 0;
    while(validate_hand(get_hand_value(hand))){
        if(get_hand_value(hand) > player_value || check_tie(player_value, dealer_value)){
            cout << "hold up" << endl;
            break;
        }
        cout << "Dealer has : " << get_hand_value(hand) << endl;
        hit_card(deck,hand);
        print.get_card_print(hand);
        dealer_value = get_hand_value(hand);
    }
    return;
}

void get_winner(int player_value, int dealer_value){
    if (player_value> 21){
        cout << "U BUST. PLAYER LOST." << endl;
    }else if (player_value == dealer_value){
        cout << "TIED GAME. RETURN CHIPS." << endl;
    }else if(player_value < dealer_value && dealer_value <=21){
        cout << "PLAYER LOST, DEALER WON." << endl;
    }else{
        cout << "PLAYER WON." << endl;
    }
    return;
}

void random_money (Player *p){
    int chips [7] = {100, 200, 250, 500, 1000, 2000, 5000};
    int random = rand()%7+1;
    cout<< "bro u got lucky u won : " << chips[random] << endl;
    p->setMoney(chips[random]);
}

void place_bet(Player *p, int &bet){
    
    while(1){
        if(bet <= p->getMoney()){
            p->setMoney((p->getMoney())-bet); 
            return;
        }else{
            cout << "bro enter valid number ? " << endl;
            cin >> bet;
        }
    }
}

void start_game(Card * deck, std::list<Card> &player_hand, std::list<Card> &dealer_hand){
    int flag =0;
    for (int i =0; i <4; i++){
        if (flag == 0){
            hit_card(deck, player_hand);
            flag = 1;
        }else {
            hit_card(deck, dealer_hand);
            flag = 0;
        }
    }
}


int play_on_console(){
    list<Card> player_hand;
    list<Card> dealer_hand;
    Card *deck;
    deck = initDeck();

    srand ( time(NULL) );
    start_game(deck,player_hand,dealer_hand);
    
    print.print_dealer_hand(dealer_hand);
    print.get_card_print(player_hand);

    //print_dealer_hand(dealer_hand);
    //get_card_print(player_hand);
    
    /*
    Player *p = new Player;
    random_money(p);
    cout << p->getMoney() << endl;
    int bet;

    cout << "bro enter valid number ? " << endl;
    cin >> bet;
    place_bet(p,bet);

    cout << "bet is : " << bet << endl;
    cout << "user money left : " << p->getMoney() << endl;

    */
    
    // give 2 cards each player-dealer-player-dealer

    /*
    cout <<"buraya geldik ??"<< endl;
    cout <<"Player: " << get_hand_value(player_hand) << endl;
    cout << "Dealer : " << get_hand_value(dealer_hand) << endl;


    std::list<Card> ::iterator it_dealer = dealer_hand.begin();
    std::advance(it_dealer,1);
    cout << "Dealer has card: " << (*it_dealer).getVal() << "-" << (*it_dealer).getColor()  << endl;


    std::list<Card> ::iterator it_player = player_hand.begin();
    cout << "You got: " << (*it_player).getVal() << "-" << (*it_player).getColor() << " ";
    std::advance(it_player,1);
    cout << (*it_player).getVal() << "-" << (*it_player).getColor() <<endl;
    cout << "In total: " << get_hand_value(player_hand)  << endl;
    */

    play_player(deck,player_hand);

    int player_value = get_hand_value(player_hand);
    if (player_value <=21){
        play_dealer(deck,dealer_hand, player_value);
    }

    cout << "You finished with : " << get_hand_value(player_hand) << endl;
    cout << "Dealer finished with : " << get_hand_value(dealer_hand) << endl;
    get_winner(get_hand_value(player_hand), get_hand_value(dealer_hand));
    
    

    return 0;

}



int main() {
    std::cout << "Hello, World!" << std::endl;
   // initDeck();
   // hearts , diamond , clubs, spades 52 cards
   // A, 2,3,4,5,6,7,8,9,10,J,Q,K
//int res = validate_hand(get_hand_value(FullHand));
    play_on_console();
    return 0;
}
