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