#include <fstream>

#include "ArquivoDados.hpp"

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
   x.setAnt(-1);
   x.setProx(this->cab->getPosCabeca());

   //faz a cabeca antiga apontar para o anterior (nova cabeca)
   if (this->cab->getPosCabeca() != -1)
   {
      NoMedico prox = this->getData(this->cab->getPosCabeca());
      if (this->cab->getPosLivre() == -1)
         prox.setAnt(this->cab->getPosTopo());
      else
         prox.setAnt(this->cab->getPosLivre());
      this->insereNo(&prox, this->cab->getPosCabeca());
   }
   
   if (this->cab->getPosLivre() == -1) //n ha Nos livres
   {
      this->insereNo(&x, this->cab->getPosTopo());
      indice = this->cab->getPosTopo();
      this->cab->setPosCabeca(this->cab->getPosTopo());
      this->cab->incTopo();
   }
   else
   {
      NoMedico aux = this->getData(this->cab->getPosLivre());
      this->insereNo(&x, this->cab->getPosLivre());
      indice = this->cab->getPosLivre();
      this->cab->setPosCabeca(this->cab->getPosLivre());
      this->cab->setPosLivre(aux.getProx());
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

void ArquivoDados::remove (int pos)
{
   NoMedico atual = this->getData(pos);

   //remocao na cabeca
   if (pos == this->cab->getPosCabeca())
   {
      this->cab->setPosCabeca(atual.getProx());
      if (atual.getProx() != -1)
      {
         NoMedico prox = this->getData(atual.getProx());
         prox.setAnt(-1);  
         this->insereNo(&prox, atual.getProx());
      }
   }
   //remocao no meio
   else
   {
      //proximo do anterior -> proximo
      NoMedico ant  = this->getData(atual.getAnt());
      ant.setProx(atual.getProx());
      this->insereNo(&ant, atual.getAnt());

      //nao eh a calda
      if (atual.getProx() != -1)
      {
         //anterior do proximo -> anterior.
         NoMedico prox = this->getData(atual.getProx());
         prox.setAnt(atual.getAnt());
         this->insereNo(&prox, atual.getProx());
      }      
   }
   //Encadeando o No removido na lista de livres
   atual.setProx(this->cab->getPosLivre());
   atual.setAnt(-1);
   this->cab->setPosLivre(pos);
   this->insereNo(&atual, pos);
   
   this->cab->setCabecalho(this->out);
}

NoMedico ArquivoDados::getData (int pos)
{
   NoMedico x;
   this->in.seekg(sizeof(CabecalhoDados) + pos * sizeof(NoMedico));
   this->in.read((char*)&x, sizeof(NoMedico));
   return x;
}

ArquivoDados::~ArquivoDados ()
{
   delete this->cab;
}