#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <string>
#include <fstream>

#include "NoMedico.hpp"

class Arquivo
{
   protected:
      std::string fileName;
      std::ifstream in;
      std::ofstream out;

      Arquivo (const std::string&);
      ~Arquivo ();   
};

#endif // !ARQUIVO_HPP