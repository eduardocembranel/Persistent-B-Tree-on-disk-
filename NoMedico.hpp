#ifndef NOMEDICO_HPP
#define NOMEDICO_HPP

#include "Medico.hpp"

class NoMedico
{
   public: //mudar para privado dps
      Medico medico;
      int prox;

   public:
      NoMedico ();
      void setMedico (Medico);
      void setProx (int);
      int getProx ();
};

#endif // !NOMEDICO_HPP