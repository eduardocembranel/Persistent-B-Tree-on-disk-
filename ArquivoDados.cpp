#include "ArquivoDados.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
using namespace std;

ArquivoDados::ArquivoDados (const std::string &fileName) : Arquivo(fileName)
{  
   this->cab = new CabecalhoDados();
   this->cab->setCabecalho(this->out); //coloca o cabecalho no arquivo
}

int ArquivoDados::insere (Medico medico)
{
   int indice;
   NoMedico x;
   x.setMedico(medico);
   x.setProx(this->cab->getPosCabeca());

   if (this->cab->getPosLivre() == -1) //n ha nós livres
   {
      this->insereNo(&x, this->cab->getPosTopo());
      indice = this->cab->getPosTopo();
      this->cab->setPosCabeca(this->cab->getPosTopo());
      this->cab->incTopo();
   }
   else
   {
      NoMedico *aux = this->getData(this->cab->getPosLivre());
      this->insereNo(&x, this->cab->getPosLivre());
      indice = this->cab->getPosLivre();
      this->cab->setPosCabeca(this->cab->getPosLivre());
      this->cab->setPosLivre(aux->getProx());
      delete aux;
   }
   this->cab->setCabecalho(this->out);
   return indice;
}

void ArquivoDados::insereNo (NoMedico *elem, int pos)
{
   this->out.seekp(sizeof(CabecalhoDados) + pos * sizeof(NoMedico));
   this->out.write((char*)elem, sizeof(NoMedico));
   this->out.flush();
}

NoMedico* ArquivoDados::getData (int pos)
{
   NoMedico *x = new NoMedico();
   this->in.seekg(sizeof(CabecalhoDados) + pos * sizeof(NoMedico));
   this->in.read((char*)x, sizeof(NoMedico));
   return x;
}

