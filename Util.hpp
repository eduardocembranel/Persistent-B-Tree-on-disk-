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
      static int strToInt (const std::string &);
      static bool ehNula(const std::string &);
      static bool ehFormatoData (const std::string &);
      static bool ehInt (const std::string &);
      static bool ehNumTraco (const std::string &);
   
   private:
      Util ();
};

#endif // !UTIL_HPP