#ifndef NOMEDICO_HPP
#define NOMEDICO_HPP

#include "Medico.hpp"

class NoMedico
{
   public: //mudar para privado dps
      Medico medico;
      int prox;
      int ant;

   public:
      NoMedico ();
      void setMedico (Medico);
      void setProx (int);
      void setAnt (int);
      int getProx ();
      int getAnt ();

};

#endif // !NOMEDICO_HPP