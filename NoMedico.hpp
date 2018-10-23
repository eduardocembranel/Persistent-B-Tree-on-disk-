#ifndef NOMEDICO_HPP
#define NOMEDICO_HPP

/*
* \file NoMedico.hpp
* \class NoMedico
* \brief Responsável por representar um nó de medico
* \author Carlos Pedroso
* \author Eduardo Cembranel
*/

#include "Medico.hpp"

class NoMedico
{
   public:
      Medico medico;
      int prox;

      /* brief: construtor padrao
      * pre: nenhuma
      * pos: nenhuma
      */
      NoMedico ();

      /* brief: setter medico
      * param: medico
      * pre: nenhuma
      * pos: medico inserido
      */
      void setMedico (Medico);

      /* brief: setter: posProx
      * param: posicao
      * pre: nenhuma
      * pos: posicao inserida
      */
      void setProx (int);

      /* brief: getter: posicao do No proximo
      * pre: nenhuma
      * pos: retorna a posicao do No proximo
      */
      int getProx ();
};

#endif // !NOMEDICO_HPP