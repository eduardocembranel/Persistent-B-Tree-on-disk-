#include "NoMedico.hpp"
#include "CabecalhoDados.hpp"
#include <iostream>

NoMedico::NoMedico ()
{

}

void NoMedico::setMedico (Medico other)
{
   this->medico = other;
}

void NoMedico::setProx (int prox)
{
   this->prox = prox;
}

int NoMedico::getProx ()
{
   return this->prox;
}