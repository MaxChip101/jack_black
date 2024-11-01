#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <cctype>
#include <algorithm>

#include "ai.h"
#include "game.h"

// Text Colors
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

// Bold Text
#define BOLD "\033[1m"
#define BOLD_OFF "\033[22m"

// Background Colors
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

std::string input()
{
    std::string inp_str;
    char ch;
    while (std::cin.get(ch) && ch != '\n') {
        inp_str += ch;
    }
    return inp_str;
}

char choice2 (std::string _choice1, std::string _choice2)
{
    // renders the prompt text with the choices
    std::cout << "   1) " << _choice1 + ", 2) " << _choice2 << std::endl;

    // user input
    std::string picked;

    std::cout << " > " << std::flush;
    picked = input();

    // if input is within the choices then exit loop
    if(picked[0] == '1' || picked[0] == '2') {
        return picked[0];
    } else {
        choice2(_choice1, _choice2);
    }

    return '0';
}

std::vector<Card> createDeck()
{
    std::vector<Card> deck;

    for (int t = 0; t < 4; t++)
    {   
        for(int r = 2; r < 11; r++)
        {
            Card card;
            card.name = std::to_string(r);
            switch(t)
            {
                case 0:
                    card.type = "Diamonds";
                    break;
                case 1:
                    card.type = "Hearts";
                    break;
                case 2:
                    card.type = "Spades";
                    break;
                case 3:
                    card.type = "Clubs";
                    break;   
            }
            card.value = r;
            deck.push_back(card);
        }
        for (int f = 0; f < 3; f++)
        {
            Card card;
            switch (f)
            {
                case 0:
                    card.name = "King";
                    break;
                case 1:
                    card.name = "Queen";
                    break;
                case 2:
                    card.name = "Jack";
                    break;
            }
            switch(t)
            {
                case 0:
                    card.type = "Diamonds";
                    break;
                case 1:
                    card.type = "Hearts";
                    break;
                case 2:
                    card.type = "Spades";
                    break;
                case 3:
                    card.type = "Clubs";
                    break;   
            }
            card.value = 10;
            deck.push_back(card);
        }
        Card card;
        card.name = "Ace";
        switch(t)
        {
            case 0:
                card.type = "Diamonds";
                break;
            case 1:
                card.type = "Hearts";
                break;
            case 2:
                card.type = "Spades";
                break;
            case 3:
                card.type = "Clubs";
                break;   
        }
            card.value = 1;
            deck.push_back(card);
    }

    return deck;
}

Card draw(std::vector<Card> &deck)
{
    if(deck.size() > 0)
    {
    int index = rand() % deck.size();
    Card card = deck[index];
    deck.erase(deck.begin()+index);
    return card;
    }
    else
    {
        Card empty_card;
        empty_card.name = "Empty";
        empty_card.type = "Empty";
        empty_card.value = 0;
        return empty_card;
    }
}

void render_card(Card card)
{
    std::cout << "  " << BG_WHITE << BOLD;
    if(card.type == "Diamonds")
    {
        std::cout << RED << " ♦ ";
    } else if(card.type == "Hearts")
    {
        std::cout << RED << " ♥ ";
    }
    else if(card.type == "Spades")
    {
        std::cout << BLACK << " ♠ ";
    }
    else if(card.type == "Clubs")
    {
        std::cout << BLACK << " ♣️ ";
    }

    std::cout << card.name << " of " << card.type;

    if(card.type == "Diamonds")
    {
        std::cout << " ♦ "; 
    }
    else if(card.type == "Hearts")
    {
        std::cout << " ♥ ";
    }
    else if(card.type == "Spades")
    {
        std::cout << " ♠ ";
    }
    else if(card.type == "Clubs")
    {
        std::cout << " ♣ ";
    }

    std::cout << RESET << std::endl;

}

std::vector<Card> logic_deck;
std::vector<Card> logic_deck2;
std::vector<Card> opponent_deck;
std::vector<Card> dealer_deck;
std::vector<Card> player_deck;

int ace_value(Card card)
{

    // tells the user to set the value of their ace, if it is above 21 then set it to 1
    render_card(card);
    std::cout << "current value: " << card.value << std::endl;
    std::cout << "What value do you want your ace to be?" << std::endl;
    char choice = choice2("1", "11");
    
    return (choice == '1') ? 1 : 11;
}


void add_opponent_card(std::vector<Card> &deck)
{
    Card drawn = draw(deck);
    
    if(drawn.name == "Ace")
    {
        drawn.value = ai2::set_ace_value();
    }

    opponent_deck.push_back(drawn);

    auto pos = std::find(logic_deck2.begin(), logic_deck2.end(), drawn);
    if (pos != logic_deck2.end())
    {
        logic_deck2.erase(pos);
    }
    
}

void add_dealer_card(std::vector<Card> &deck)
{
    Card drawn = draw(deck);
    
    if(drawn.name == "Ace")
    {
        drawn.value = ai::set_ace_value();
    }

    dealer_deck.push_back(drawn);

    auto pos = std::find(logic_deck.begin(), logic_deck.end(), drawn);
    if (pos != logic_deck.end())
    {
        logic_deck.erase(pos);
    }
    
}

void show_player_deck()
{
    std::cout << "--------------------------------------------------\nYour Cards:" << std::endl;   
    for(size_t i = 0; i < player_deck.size(); i++)
    {
        render_card(player_deck[i]);
    }

    for(size_t i = 0; i < player_deck.size(); i++)
    {
        if(player_deck[i].name == "Ace")
        {
            std::cout << "--------------------------------------------------" << std::endl;
            player_deck[i].value = ace_value(player_deck[i]);
        }
    }
}

void game(std::vector<Card> &deck)
{
    bool on = true;

    add_dealer_card(deck);
    add_dealer_card(deck);

    player_deck.push_back(draw(deck));
    player_deck.push_back(draw(deck));

    add_opponent_card(deck);
    add_opponent_card(deck);

    ai::update_biases(logic_deck);
    ai::update_deck(dealer_deck);

    ai2::update_biases(logic_deck2);
    ai2::update_deck(opponent_deck);

    show_player_deck();

    bool empty_deck = false;

    while(on)
    {
        std::cout << "Do you stay or hit?" << std::endl;
        char choice = choice2("Stay", "Hit");
        if(choice == '1')
        {
            on = false;
        }
        else
        {
            Card drawn = draw(deck);

            if (drawn.name != "Empty")
            {
                player_deck.push_back(drawn);
                show_player_deck();    
                
                int points = 0;
                for(size_t i = 0; i < player_deck.size(); i++)
                {
                    points += player_deck[i].value;
                }
                if(points > 21)
                {
                    std::cout << RED << "You Busted" << RESET << std::endl;
                    on = false;
                }
            }
            else
            {
                std::cout << RED << "Deck is empty" << RESET << std::endl;
                on = false;
                empty_deck = true;
            }
        }
    }

    on = true;

    while(on && !empty_deck)
    {
        bool choice = ai::decide();
        
        if(choice == true)
        {
            add_dealer_card(deck);
            ai::update_deck(dealer_deck);
            ai::update_biases(logic_deck);
        }
        else
        {
            on = false;
        }
    }

    on = true;

    while(on && !empty_deck)
    {
        bool choice = ai2::decide();
        
        if(choice == true)
        {
            add_opponent_card(deck);
            ai2::update_deck(opponent_deck);
            ai2::update_biases(logic_deck2);
        }
        else
        {
            on = false;
        }
    }

    int dealer_points = 0;

    std::cout << "--------------------------------------------------\nDealer Cards:" << std::endl;

    for(size_t i = 0; i < dealer_deck.size(); i++)
    {
        dealer_points += dealer_deck[i].value;
        render_card(dealer_deck[i]);
    }

    int opponent_points = 0;

    std::cout << "--------------------------------------------------\nOpponent Cards:" << std::endl;

    for(size_t i = 0; i < opponent_deck.size(); i++)
    {
        opponent_points += opponent_deck[i].value;
        render_card(opponent_deck[i]);
    }


    int player_points = 0;

    for(size_t i = 0; i < player_deck.size(); i++)
    {
        player_points += player_deck[i].value;
    }

    int winner = 0;

    // checking for the winner with math::max() and if below 21
    if(player_points <= 21 && opponent_points <= 21 && dealer_points <= 21) // everybody below 21
    {
        winner = std::max(player_points, std::max(opponent_points, dealer_points));
    }
    else if(player_points <= 21 && opponent_points <= 21) // player and opponent below 21
    {
        winner = std::max(player_points,opponent_points);
    }
    else if(player_points <= 21 && dealer_points <= 21) // player and dealer below 21
    {
        winner = std::max(player_points, dealer_points);
    }
    else if(dealer_points <= 21 && opponent_points <= 21) // opponent and dealer below 21
    {
        winner = std::max(opponent_points, dealer_points);
    }
    else if(dealer_points <= 21) // only dealer below 21
    {
        winner = dealer_points;
    }
    else if(player_points <= 21) // only player below 21
    {
        winner = player_points;
    }
    else if(opponent_points <= 21) // only opponent below 21
    {
        winner = opponent_points;
    }


    bool all_busts = true;

    if(player_points <= 21 || opponent_points <= 21 || dealer_points <= 21) // if one person is below 21 then turn off the all busts boolean
    {
        all_busts = false;
    }

    int tieCount = 0;
    if ((player_points == winner || opponent_points == winner || dealer_points == winner) && !all_busts) // checks for ties
    {
        tieCount++;
    }

    // check the game for the endings
    if(all_busts) // everyone busted
    {
        std::cout << "Nobody Won" << std::endl;
    }
    else if(tieCount == 2) // ties
    {
        std::cout << "2 or more players tied" << std::endl;
    }
    else if(winner == player_points && player_points <= 21 && !all_busts) // player wins
    {
        std::cout << "You Win!" << std::endl;
    }
    else if(winner == opponent_points && opponent_points <= 21 && !all_busts) // opponent wins
    {
        std::cout << "Opponent Wins, you lose" << std::endl;
    }
    else if(winner == dealer_points && dealer_points <= 21) // dealer wins
    {
        std::cout << "Dealer Wins, you lose" << std::endl;
    }
    else // if all else then unkown
    {
        std::cout << "Unkown" << std::endl;
    }

    std::cout << "player: " << player_points << ", opponent: " << opponent_points << ", dealer: " << dealer_points << std::endl;
    std::cout << "Press Enter to escape";
    input();
}

int main()
{
    #ifdef _WIN32
    system("chcp 65001"); // sets console to UTF-8 if on windows
    #endif

    srand(time(NULL));
    std::vector<Card> deck = createDeck();
    logic_deck = deck;
    game(deck);
}