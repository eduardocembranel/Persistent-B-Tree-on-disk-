#include "NoMedico.hpp"
#include "CabecalhoDados.hpp"
#include <iostream>

NoMedico::NoMedico () {}

void NoMedico::setMedico (Medico other)
{
   this->medico = other;
}

void NoMedico::setProx (int prox)
{
   this->prox = prox;
}

void NoMedico::setAnt (int ant)
{
   this->ant = ant;
}

int NoMedico::getAnt ()
{
   return this->ant;
}

int NoMedico::getProx ()
{
   return this->prox;
}