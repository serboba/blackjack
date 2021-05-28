#include <iostream>
#include "card.h"
#include "player.h"
#include "printer.h"
#include <stack>
#include <list>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include <random>

using namespace std;
Printer print;




Card * initDeck(){
    Card *deck = new Card[52];
    string colors [4] = {"hearts" , "diamonds", "clubs", "spades"};
    const char cardtypes[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    for(int j = 0; j<4; j++) {
        for (int i = 0; i < 13; i++) {
            Card c(cardtypes[i],colors[j], 0);
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
            if (ace_flag==0 && value< 11) {
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
        }
        if(value >21 && ace_flag == 1){
            value -= 10;
            ace_flag=0;
        }
    }
    //cout<< "finito: " << value <<endl;
    return value;
}

int validate_hand(int value){
    if(value>21){
        //cout << "U BUST" <<endl;
        return 0;
    }else if(value ==21){
        //cout << "BLACKJACK?? STOP" << endl;
        return 2;
    }else{
        //cout << "U CAN HIT" << endl;
        return 1;
    }
}

void hit_card(Card deck[], std::list<Card> &hand){
    int random = std::rand() %51 +1;
    
    while(1){
        random = std::rand()%51 + 1;
        if ((deck[random]).getFlag() != 1){
            //cout <<"U HIT: " <<(deck[random]).getVal() <<"-"<<(deck[random]).getColor() << endl;
            hand.push_back((deck[random]));
            (deck[random]).setFlag(1);
            break;
        }
    }
}


void play_player(Card *deck, std::list<Card> &hand, Player &p, int &bet){
    char req;
    if(get_hand_value(hand) == 21){
        //cout << "BLACKJACK U WON." <<  endl;
        return;
    }
    int flag = 0;
    while(validate_hand(get_hand_value(hand))){
        cout << "Your hand now: " << get_hand_value(hand) << endl;
        cout << "Type 'h' for hit, 'd' for double, 's' for stand" << endl;
        cin >> req;
        switch (req)
        {
        case 'h':
            hit_card(deck, hand);
            break;
        case 'd':
            // hit break double chips?
            if(p.getMoney()>=bet){                
                hit_card(deck,hand);
                p.withdraw(bet);
                bet *= 2;
                flag = 1;
                cout << "bro bet is : " << bet << " and yo balance : " << p.getMoney() <<endl;
            }else{
                cout << "bro u broke lmao" << endl;
            }
            break;
        case 's':
            flag = 1;
            break;
        default:
            
            break;
        }
        print.get_card_print(hand);
        cout << "Your hand now: " << get_hand_value(hand) << endl;
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
    print.get_card_print(hand);
    cout << "Dealer has before he draws: " << get_hand_value(hand) << endl;
    if(check_tie(player_value, get_hand_value(hand) ==1)){
        return;
    }
    while(validate_hand(get_hand_value(hand))){
        if(get_hand_value(hand) > player_value || check_tie(player_value, dealer_value)){
            //cout << "hold up" << endl;
            break;
        }
        Sleep(3000);
        hit_card(deck,hand);
        print.get_card_print(hand);
        dealer_value = get_hand_value(hand);

        cout << "Dealer has : " << get_hand_value(hand) << endl;
        Sleep(3000);
    }
    return;
}

int get_winner(int player_value, int dealer_value){
    if (player_value> 21){
        cout << R"(  $$$$$$$\  $$\   $$\  $$$$$$\ $$$$$$$$\       $$\     $$\  $$$$$$\  $$\   $$\       $$\       $$$$$$\   $$$$$$\ $$$$$$$$\ )"<<endl;
        cout << R"(  $$  __$$\ $$ |  $$ |$$  __$$\\__$$  __|      \$$\   $$  |$$  __$$\ $$ |  $$ |      $$ |     $$  __$$\ $$  __$$\\__$$  __|)"<<endl;
        cout << R"(  $$ |  $$ |$$ |  $$ |$$ /  \__|  $$ |          \$$\ $$  / $$ /  $$ |$$ |  $$ |      $$ |     $$ /  $$ |$$ /  \__|  $$ |   )"<<endl;
        cout << R"(  $$$$$$$\ |$$ |  $$ |\$$$$$$\    $$ |           \$$$$  /  $$ |  $$ |$$ |  $$ |      $$ |     $$ |  $$ |\$$$$$$\    $$ |   )"<<endl;
        cout << R"(  $$  __$$\ $$ |  $$ | \____$$\   $$ |            \$$  /   $$ |  $$ |$$ |  $$ |      $$ |     $$ |  $$ | \____$$\   $$ |   )"<<endl;
        cout << R"(  $$ |  $$ |$$ |  $$ |$$\\   $$ |  $$ |             $$ |    $$ |  $$ |$$ |  $$ |      $$ |     $$ |  $$ |$$\\   $$ |  $$ |   )"<<endl;
        cout << R"(  $$$$$$$  |\\$$$$$$  |\\$$$$$$  |  $$ |             $$ |     $$$$$$  |\\$$$$$$  |      $$$$$$$$\\ $$$$$$  |\\$$$$$$  |  $$ |   )"<<endl;
        cout << "  \\_______/  \\______/  \\______/   \\__|             \\__|     \\______/  \\______/       \\________|\\______/  \\______/   \\__|   "<<endl;

        Sleep(5000);

        return 0;
    }else if (player_value == dealer_value){
        cout <<"  $$$$$$$$\\ $$$$$$\\ $$$$$$$$\\ $$$$$$$\\         $$$$$$\\   $$$$$$\\  $$\\      $$\\ $$$$$$$$\\ " << endl;
        cout <<"  \\__$$  __|\\_$$  _|$$  _____|$$  __$$\\       $$  __$$\\ $$  __$$\\ $$$\\    $$$ |$$  _____|" << endl;
        cout <<"     $$ |     $$ |  $$ |      $$ |  $$ |      $$ /  \\__|$$ /  $$ |$$$$\\  $$$$ |$$ |      " << endl;
        cout <<"     $$ |     $$ |  $$$$$\\    $$ |  $$ |      $$ |$$$$\\ $$$$$$$$ |$$\\$$\\$$ $$ |$$$$$\\    " << endl;
        cout <<"     $$ |     $$ |  $$  __|   $$ |  $$ |      $$ |\\_$$ |$$  __$$ |$$ \\$$$  $$ |$$  __|   " << endl;
        cout <<"     $$ |     $$ |  $$ |      $$ |  $$ |      $$ |  $$ |$$ |  $$ |$$ |\\$  /$$ |$$ |      " << endl;
        cout <<"     $$ |   $$$$$$\\ $$$$$$$$\\ $$$$$$$  |      \\$$$$$$  |$$ |  $$ |$$ | \\_/ $$ |$$$$$$$$\\ " << endl;
        cout <<"     \\__|   \\______|\\________|\\_______/        \\______/ \\__|  \\__|\\__|     \\__|\\________|" << endl;

        Sleep(5000);
            return 1;
    }else if(player_value < dealer_value && dealer_value <=21){
        cout << "  $$$$$$$\\  $$$$$$$$\\  $$$$$$\\  $$\\       $$$$$$$$\\ $$$$$$$\\        $$\\      $$\\  $$$$$$\\  $$\\   $$\\ " << endl;
        cout << "  $$  __$$\\ $$  _____|$$  __$$\\ $$ |      $$  _____|$$  __$$\\       $$ | $\\  $$ |$$  __$$\\ $$$\\  $$ |" << endl;
        cout << "  $$ |  $$ |$$ |      $$ /  $$ |$$ |      $$ |      $$ |  $$ |      $$ |$$$\\ $$ |$$ /  $$ |$$$$\\ $$ |" << endl;
        cout << "  $$ |  $$ |$$$$$\\    $$$$$$$$ |$$ |      $$$$$\\    $$$$$$$  |      $$ $$ $$\\$$ |$$ |  $$ |$$ $$\\$$ |" << endl;
        cout << "  $$ |  $$ |$$  __|   $$  __$$ |$$ |      $$  __|   $$  __$$<       $$$$  _$$$$ |$$ |  $$ |$$ \\$$$$ |" << endl;
        cout << "  $$ |  $$ |$$ |      $$ |  $$ |$$ |      $$ |      $$ |  $$ |      $$$  / \\$$$ |$$ |  $$ |$$ |\\$$$ |" << endl;
        cout << "  $$$$$$$  |$$$$$$$$\\ $$ |  $$ |$$$$$$$$\\ $$$$$$$$\\ $$ |  $$ |      $$  /   \\$$ | $$$$$$  |$$ | \\$$ |" << endl;
        cout << "  \\_______/ \\________|\\__|  \\__|\\________|\\________|\\__|  \\__|      \\__/     \\__| \\______/ \\__|  \\__|" << endl;

        Sleep(5000);
        return 0;
    }else{
        cout << "  $$\\     $$\\  $$$$$$\\  $$\\   $$\\       $$\\      $$\\  $$$$$$\\  $$\\   $$\\  " <<endl;
        cout << "  \\$$\\   $$  |$$  __$$\\ $$ |  $$ |      $$ | $\\  $$ |$$  __$$\\ $$$\\  $$ | " <<endl;
        cout << "   \\$$\\ $$  / $$ /  $$ |$$ |  $$ |      $$ |$$$\\ $$ |$$ /  $$ |$$$$\\ $$ | " <<endl;
        cout << "    \\$$$$  /  $$ |  $$ |$$ |  $$ |      $$ $$ $$\\$$ |$$ |  $$ |$$ $$\\$$ | " <<endl;
        cout << "     \\$$  /   $$ |  $$ |$$ |  $$ |      $$$$  _$$$$ |$$ |  $$ |$$ \\$$$$ | " <<endl;
        cout << "      $$ |    $$ |  $$ |$$ |  $$ |      $$$  / \\$$$ |$$ |  $$ |$$ |\\$$$ | " <<endl;
        cout << "      $$ |     $$$$$$  |\\$$$$$$  |      $$  /   \\$$ | $$$$$$  |$$ | \\$$ | " <<endl;
        cout << "      \\__|     \\______/  \\______/       \\__/     \\__| \\______/ \\__|  \\__| " <<endl;

        Sleep(5000);
        return 2;
    }
    return 0;
}

Player random_money (){
    int chips [7] = {100, 200, 250, 500, 1000, 2000, 5000};
    int random = std::rand()%6+1;
    cout<< "bro u got lucky u won : " << endl;
cout<<"          ,/`."<<endl;
cout<<"        ,'/ $$`." <<endl;
cout<<"      ,'_/_  _ _`.   "<< chips[random] <<"$" << endl;
cout<<"    ,'__/_ ___ _  `."<<endl;
cout<<"  ,'_  /___ __ _ __ `."<<endl;
cout<<" '-.._/___...-$$$-..__`."<<endl;

    Player p(0,chips[random]);
    return p;
}

void place_bet(Player *p, int &bet){
    int flag = 0;
    while(flag!=1){
        cout << ":(" << endl;
        if(bet <= p->getMoney()){
            p->setMoney((p->getMoney())-bet); 
            flag=1;
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

    //print_dealer_hand(dealer_hand);
    //get_card_print(player_hand);

    srand ( time(NULL) );

    Player p;
    p = random_money();
    cout << p.getMoney() << endl;
    int bet;

    while(p.getMoney()>0){
    
    list<Card> player_hand;
    list<Card> dealer_hand;
    Card *deck;
    deck = initDeck();


    cout << "you got : " << p.getMoney() <<"$" << endl;
    cout << "bro enter valid number ? " << endl;
    cin >> bet;
    place_bet(&p,bet);

    cout << "bet is : " << bet<<"$" << endl;
    cout << "your new balance kek: " << p.getMoney()<<"$" << endl;



    start_game(deck,player_hand,dealer_hand);
    
    print.print_dealer_hand(dealer_hand);
    print.get_card_print(player_hand);

    if(get_hand_value(player_hand)==21){
    cout << " $$$$$$$\\  $$\\        $$$$$$\\   $$$$$$\\  $$\\   $$\\   $$$$$\\  $$$$$$\\   $$$$$$\\  $$\\   $$\\  "<<endl;
    cout << " $$  __$$\\ $$ |      $$  __$$\\ $$  __$$\\ $$ | $$  |  \\__$$ |$$  __$$\\ $$  __$$\\ $$ | $$  |"<<endl;
    cout <<"  $$ |  $$ |$$ |      $$ /  $$ |$$ /  \\__|$$ |$$  /      $$ |$$ /  $$ |$$ /  \\__|$$ |$$  /  "<<endl;
    cout <<"  $$$$$$$\\ |$$ |      $$$$$$$$ |$$ |      $$$$$  /       $$ |$$$$$$$$ |$$ |      $$$$$  /  "<<endl;
    cout <<"  $$  __$$\\ $$ |      $$  __$$ |$$ |      $$  $$<  $$\\   $$ |$$  __$$ |$$ |      $$  $$<   "<<endl;
    cout <<"  $$ |  $$ |$$ |      $$ |  $$ |$$ |  $$\\ $$ |\\$$\\ $$ |  $$ |$$ |  $$ |$$ |  $$\\ $$ |\\$$\\  "<<endl;
    cout <<"  $$$$$$$  |$$$$$$$$\\ $$ |  $$ |\\$$$$$$  |$$ | \\$$\\\\$$$$$$  |$$ |  $$ |\\$$$$$$  |$$ | \\$$\\ "<<endl;
    cout <<"  \\_______/ \\________|\\__|  \\__| \\______/ \\__|  \\__|\\______/ \\__|  \\__| \\______/ \\__|  \\__| "<<endl;                                                                                   
    cout << "YOU WON" << endl;
    int m = p.getMoney();
    m += bet*(3/2);
    p.setMoney(m);
        continue;
    }

    
    
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

    play_player(deck,player_hand,p,bet);

    cout<<"NOW IS DEALERS TURN. DEALERS HAND:" << endl;
    print.print_dealer_hand(dealer_hand);
    Sleep(5000);
    int player_value = get_hand_value(player_hand);
    if (player_value <=21){
        play_dealer(deck,dealer_hand, player_value);
    }

    cout << "You finished with : " << get_hand_value(player_hand) << endl;
    cout << "Dealer finished with : " << get_hand_value(dealer_hand) << endl;
    int end = get_winner(get_hand_value(player_hand), get_hand_value(dealer_hand));
    
    if(end==0){
        cout << "U LOST: " << bet <<"$" << ", YO MONEY LEFT : " << p.getMoney()<<"$" << endl;
        //lost - deposit amount
    }else if(end ==1){
        p.deposit(bet);
        cout << "TIED GAME, RETURNS STAKES, YOUR ACC: " << p.getMoney()<<"$" << endl;
        // tied game no loss
    }else{
        p.deposit(2*bet);
        cout << "U WON " << (2*bet) <<"$" << " YOUR NEW BALANCE: " << p.getMoney() <<"$" << endl;
        // returns 2, player win
    }
}

    Sleep(5000);
    return 0;

}



int main() {
    play_on_console();
    return 0;
}
