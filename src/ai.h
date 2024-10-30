#ifndef AI_H
#define AI_H

#include <vector>
#include "game.h"

namespace ai
{
    void update_deck(std::vector<Card> deck);
    void update_biases(std::vector<Card> deck);
    int set_ace_value();
    bool decide();
}

namespace ai2
{
    void update_deck(std::vector<Card> deck);
    void update_biases(std::vector<Card> deck);
    int set_ace_value();
    bool decide();
}

#endif