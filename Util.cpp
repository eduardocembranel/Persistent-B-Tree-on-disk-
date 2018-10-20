#include <cstdlib>
#include <iostream>
#include <sstream>
#include <limits>
#include <cctype>

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
   std::cout << "\nPressione ENTER para retornar...";
   Util::flushInput();
}

void Util::flushInput ()
{
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Util::strToInt (const std::string &str)
{
   int elem;
   istringstream (str) >> elem;
   return elem;
}

bool Util::ehNula(const std::string &str)
{
   return str.size() == 0;
}

bool Util::ehFormatoData (const std::string &str)
{
   if (str.size() != 10) 
      return false;

   if (str[2] != '/' || str[5] != '/')
      return false;
   
   if (!isdigit(str[0]) || !isdigit(str[1]) || !isdigit(str[3]) ||
      !isdigit(str[4]) || !isdigit(str[6]) || !isdigit(str[7]) ||
      !isdigit(str[8]) || !isdigit(str[9]))
      return false;

   return true;
}

bool Util::ehNumTraco (const std::string &str)
{
   for (char it : str)
      if (it != '/' && !isdigit(it))
         return false;
   return true;
}

bool Util::ehInt (const std::string &str)
{
   char *fim;
   strtol(str.c_str(), &fim, 10);

   return (*fim == 0);
}     