#ifndef GAME_H
#define GAME_H

#include <string>

struct Card
{
    std::string name;
    std::string type;
    int value;

    bool operator==(const Card &other) const
    {
        return value == other.value;
    }

};

#endif