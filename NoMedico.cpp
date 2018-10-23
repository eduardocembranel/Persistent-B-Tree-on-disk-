#include "NoMedico.hpp"
#include "CabecalhoDados.hpp"
#include <iostream>

/* brief: construtor padrao
* pre: nenhuma
* pos: nenhuma
*/
NoMedico::NoMedico () {}

/* brief: setter medico
* param: medico
* pre: nenhuma
* pos: medico inserido
*/
void NoMedico::setMedico (Medico other)
{
   this->medico = other;
}

/* brief: setter: posProx
* param: posicao
* pre: nenhuma
* pos: posicao inserida
*/
void NoMedico::setProx (int prox)
{
   this->prox = prox;
}

/* brief: getter: posicao do No proximo
* pre: nenhuma
* pos: retorna a posicao do No proximo
*/
int NoMedico::getProx ()
{
   return this->prox;
}