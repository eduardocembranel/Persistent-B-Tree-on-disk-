#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <cstdio>
#include <string>
#include <fstream>
#include "NoMedico.hpp"

class Arquivo
{
   public: //mudar para protected dps
      std::string fileName;
      std::ifstream in;
      std::ofstream out;

      Arquivo (const std::string&);
   
   public:
     // virtual void insere (Medico);
     // virtual NoMedico* getData (int);
      
};

#endif // !ARQUIVO_HPP