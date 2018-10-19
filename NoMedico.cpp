#include "NoMedico.hpp"
#include "CabecalhoDados.hpp"
#include <iostream>
using namespace std;
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
 //  this->fBuffer = fopen(fileName.c_str(), "rb");
 //  NoMedico *x = new NoMedico();
 //  fseek(this->fBuffer, sizeof(CabecalhoDados) + pos * sizeof(NoMedico), SEEK_SET);
 //  fread(x, sizeof(NoMedico), 1, this->fBuffer);
 //  fclose(this->fBuffer);
 //  cout << "plz" << x->medico.nome;
