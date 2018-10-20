#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>

class Util
{
   public:
      static std::vector<std::string> splitString (std::string, char);
   private:
      Util ();
};

#endif // !UTIL_HPP