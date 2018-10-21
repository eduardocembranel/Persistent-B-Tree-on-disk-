#ifndef ARQUIVODADOS_HPP
#define ARQUIVODADOS_HPP

#include <string>

#include "Arquivo.hpp"
#include "CabecalhoDados.hpp"

class ArquivoDados : public Arquivo
{
   private:
      CabecalhoDados *cab;

   public:
      ArquivoDados (const std::string&);
      int insere (Medico);
      void remove (int);
      void insereNo (NoMedico*, int);
      NoMedico getData (int);
      ~ArquivoDados ();
      
   private:
      
};

#endif // !ARQUIVODADOS_HPP