#pragma once
#include <vector>
#include <cstdlib>
#include "CharPosition.h"
#include <ncurses.h>
class Item
{
public:
    int timeCheck = 0;
    std::vector<CharPosition> data;
    bool eatPoison = false;
    bool eatFruit = false;

    Item()
    {
        int maxwidth= 94, maxheight=39;
        data.push_back(CharPosition(rand() % (maxwidth - 1) + 1, rand() % (maxheight - 1) + 1));
    }
    virtual void Print() = 0;
};