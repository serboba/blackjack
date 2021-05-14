
#ifndef BLACKJACK_PRINTER_H
#define BLACKJACK_PRINTER_H

#include <string>
#include <list>
#include "card.h"
using namespace std;

class Printer {
    
public:
    Printer();
    
    std::string get_symbol(std::string s){
    if(s.compare("diamonds")==0){
            return "♦";
        }else if(s.compare("hearts")==0){
            return "♥";
        }else if(s.compare("spades")==0){
            return "♠";
        }else{ // clubs
            return "♣";
        }
    return "";
    }


    void get_card_print(std::list<Card> &hand){

        string s="";
        for(Card c: hand){
            s+= "┌─────────┐ ";
        }
        s+= "\n";
        for (Card c: hand){   
            string value;
            if(c.getVal()=='T'){
                value.push_back('1');
                value.push_back('0'); 
            }else{
                value.push_back(c.getVal());
            }
            s+= "│ ";
            s+=value;   
            
            if(value.compare("10")== 0){
                s+="      │ ";
            }else{
                s+="       │ ";
            }
        }
        s+="\n";

        for(Card c: hand){
            s+= "│         │ ";
        }            
        s+="\n";

        for(Card c: hand){
            s+= "│         │ ";
        }
        s+="\n";

        for(Card c : hand){
            string symbol = get_symbol(c.getColor());     
            s+= "│    ";
            s+=symbol;
            s+="    │ ";
        }
        s+="\n";
        
        for(Card c: hand){
            s+= "│         │ ";
        }
        s+="\n";
        
        for(Card c: hand){
            s+= "│         │ ";
        }
        s+="\n";

        for(Card c: hand){
            string value;
            if(c.getVal()=='T'){
                value.push_back('1');
                value.push_back('0'); 
            }else{
                value.push_back(c.getVal());
            }
            
                if(value.compare("10")== 0){
                    s+= "│      ";
                }else{
                    s+= "│       ";
                }
                s+=value;
                s+=" │ ";
        }
        s+="\n";
        
        for(Card c: hand){
            s+= "└─────────┘ ";
        }
        s+="\n";
    
    cout << s << endl;          
    }

    void print_dealer_hand(std::list<Card> &hand){
    int i = 0;
    string s = "";
    for (Card c : hand){
        s+="┌─────────┐ ";
    }
    s+= "\n";
        
    for (Card c: hand){   
        if(i==0){
            s+="│░░░░░░░░░│ ";
            i+=1;

        } else{
            string value;
            if(c.getVal()=='T'){
                value.push_back('1');
                value.push_back('0'); 
            }else{
                value.push_back(c.getVal());
            }
            s+= "│ ";
            s+=value;   
                
            if(value.compare("10")== 0){
                s+="      │ ";
            }else{
                s+="       │ ";
            }
            }
        }
        s+="\n";
        i=0;

        for(Card c: hand){
            if(i==0){
                s+="│░░░░░░░░░│ ";
                i+=1;

            }else{ 
                s+= "│         │ ";
            }
        }            
        s+="\n";
        i=0;

        for(Card c: hand){
            if(i==0){
                s+="│░░░░░░░░░│ ";
            i+=1;

            }else{ 
                s+= "│         │ ";
                i+=1;
            }
        }   
        s+="\n";
        i=0;

        for(Card c : hand){
            if(i==0){
                s+="│░░░░░░░░░│ ";
            i+=1;

            }else{
            string symbol = get_symbol(c.getColor());     
            s+= "│    ";
            s+=symbol;
            s+="    │ ";
            }
        }
        s+="\n";
        i =0;


         for(Card c: hand){
            if(i==0){
                s+="│░░░░░░░░░│ ";
                i+=1;

            }else{ 
                s+= "│         │ ";
            }
        }   
        s+="\n";
        i=0;
         for(Card c: hand){
            if(i==0){
                s+="│░░░░░░░░░│ ";
                i+=1;

            }else{ 
                s+= "│         │ ";
            }
        }   
        s+="\n";
        i=0;

        for(Card c: hand){
            if(i==0){
                s+="│░░░░░░░░░│ ";
                i+=1;

            }else{
            string value;
            if(c.getVal()=='T'){
                value.push_back('1');
                value.push_back('0'); 
            }else{
                value.push_back(c.getVal());
            }
            
                if(value.compare("10")== 0){
                    s+= "│      ";
                }else{
                    s+= "│       ";
                }
                s+=value;
                s+=" │ ";
                
        }
        }
        s+="\n";
        
        for(Card c: hand){
            s+= "└─────────┘ ";
        }
        s+="\n";
    cout << s << endl;

}
    
    

};

#endif //BLACKJACK_PRINTER_H
