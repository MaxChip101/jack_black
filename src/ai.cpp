#include <string>
#include <iostream>
#include <random>
#include <vector>

#include "ai.h"
#include "game.h"

namespace ai // dealer
{
    float biases[10];
    int values[10] = {
        2, 3, 4, 5, 6, 7, 8, 9, 10, 1
    };

    std::vector<Card> ai_deck;

    int value_from_biases()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution<> dist(&biases[0], &biases[9]);

        int index = dist(gen);
        return values[index];
    }

    float bias_calculator(int value, std::vector<Card> deck)
    {
        int count = 0;
        for(size_t i = 0; i < deck.size(); i++)
        {
            if (deck[i].value == value)
            {
                count++;
            }
        }
        return float(count)/float(deck.size());
    }
    
    void update_deck(std::vector<Card> deck)
    {
        ai_deck.swap(deck);
    }

    void update_biases(std::vector<Card> deck)
    {
        biases[0] = bias_calculator(2, deck);
        biases[1] = bias_calculator(3, deck);
        biases[2] = bias_calculator(4, deck);
        biases[3] = bias_calculator(5, deck);
        biases[4] = bias_calculator(6, deck);
        biases[5] = bias_calculator(7, deck);
        biases[6] = bias_calculator(8, deck);
        biases[7] = bias_calculator(9, deck);
        biases[8] = bias_calculator(10, deck);
        biases[9] = bias_calculator(1, deck);
    }

    int set_ace_value()
    {
        int points = 0;

        for(size_t i = 0; i < ai_deck.size(); i++)
        {
            points += ai_deck[i].value;
        }

        int value = 0;

        if(points + 11 > 21)
        {
            value = 1;
        }
        else
        {
            value = 11;
        }

        return value;
    }

    bool decide()
    {
        int points = 0;

        for(size_t i = 0; i < ai_deck.size(); i++)
        {
            points += ai_deck[i].value;
        }

        int value = value_from_biases();

        if (points + value <= 21) // if it is an ace then calculate the maximum ace value one card in
        {
            return true;
        }
        else
        {
            return false;
        }

    }

} 

namespace ai2 // opponent
{
    float biases[10];
    int values[10] = {
        2, 3, 4, 5, 6, 7, 8, 9, 10, 1
    };

    std::vector<Card> ai_deck;

    int value_from_biases()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution<> dist(&biases[0], &biases[9]);

        int index = dist(gen);
        return values[index];
    }

    float bias_calculator(int value, std::vector<Card> deck)
    {
        int count = 0;
        for(size_t i = 0; i < deck.size(); i++)
        {
            if (deck[i].value == value)
            {
                count++;
            }
        }
        return float(count)/float(deck.size());
    }
    
    void update_deck(std::vector<Card> deck)
    {
        ai_deck.swap(deck);
    }

    void update_biases(std::vector<Card> deck)
    {
        biases[0] = bias_calculator(2, deck);
        biases[1] = bias_calculator(3, deck);
        biases[2] = bias_calculator(4, deck);
        biases[3] = bias_calculator(5, deck);
        biases[4] = bias_calculator(6, deck);
        biases[5] = bias_calculator(7, deck);
        biases[6] = bias_calculator(8, deck);
        biases[7] = bias_calculator(9, deck);
        biases[8] = bias_calculator(10, deck);
        biases[9] = bias_calculator(1, deck);
    }

    int set_ace_value()
    {
        int points = 0;

        for(size_t i = 0; i < ai_deck.size(); i++)
        {
            points += ai_deck[i].value;
        }

        int value = 0;

        if(points + 11 > 21)
        {
            value = 1;
        }
        else
        {
            value = 11;
        }

        return value;
    }

    bool decide()
    {
        int points = 0;

        for(size_t i = 0; i < ai_deck.size(); i++)
        {
            points += ai_deck[i].value;
        }

        int value = value_from_biases();

        if (points + value <= 21) // if it is an ace then calculate the maximum ace value one card in
        {
            return true;
        }
        else
        {
            return false;
        }

    }

} 
