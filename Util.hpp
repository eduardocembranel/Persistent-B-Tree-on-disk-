#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>

class Util
{
   public:
      static std::vector<std::string> splitString (std::string, char);
      static void clear ();
      static void pressRetornar();
      static void flushInput ();
   private:
      Util ();
};

#endif // !UTIL_HPP