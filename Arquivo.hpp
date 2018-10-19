#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <cstdio>
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
   
   public:
      virtual void insere (Medico) = 0;
      virtual NoMedico* getData (int) = 0;
      
};

#endif // !ARQUIVO_HPP