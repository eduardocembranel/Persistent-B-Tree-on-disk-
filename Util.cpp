#include <cstdlib>
#include <iostream>
#include <limits>

#include "Util.hpp"

using namespace std;

Util::Util () {}

std::vector<std::string> Util::splitString (std::string s, char c)
{
    int len = s.length();
    vector<string> subArray;

    for (int j = 0, k = 0; j < len; ++j) 
    {
        if (s[j] == c) 
        {
            string ch = s.substr(k, j - k);
            k = j+1;
            subArray.push_back(ch);
        }
        if (j == len - 1) 
        {
            string ch = s.substr(k, j - k + 1);
            subArray.push_back(ch);
        }
    }
    return subArray;
}

void Util::clear ()
{
   system("cls");
}

void Util::pressRetornar ()
{
   std::cout << "\nPressione qualquer tecla para retornar...";
   Util::flushInput();
}

void Util::flushInput ()
{
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}