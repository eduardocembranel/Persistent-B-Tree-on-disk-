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
      void insere (Medico);
      NoMedico* getData (int);

   private:
      void insereNo (NoMedico*, int);
};

#endif // !ARQUIVODADOS_HPP