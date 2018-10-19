#include "ArquivoIndice.hpp"
#include <iostream>
using namespace std;

ArquivoIndice::ArquivoIndice (const std::string &fileName) : Arquivo(fileName)
{  
   this->cab = new CabecalhoIndice();
   this->cab->setCabecalho(this->out); //coloca o cabecalho no arquivo
}

void ArquivoIndice::insere (int chave, int indice)
{
   //arvore vazia
   if (this->cab->getPosRaiz() == -1)
   {
      BTreeNode *raiz = new BTreeNode(chave, indice, this->cab->getPosRaiz());
      if (this->cab->getPosLivre() == -1)
      {
         raiz->setNode(this->out, this->cab->getPosTopo());
         this->cab->setPosRaiz(this->cab->getPosTopo());
         this->cab->incTopo();
      }
      else
      {
         BTreeNode *aux = BTreeNode::getNode(this->in, this->cab->getPosLivre());
         raiz->setNode(this->out, this->cab->getPosLivre());
         this->cab->setPosRaiz(this->cab->getPosLivre());
         this->cab->setPosLivre(aux->getProx());
         delete aux;
      }
   }
   else if (insereAux(this->cab->getPosRaiz(), chave, indice) == true) //insere e se deu overflow
   {

   }
   this->cab->setCabecalho(this->out);
}

bool ArquivoIndice::insereAux (int pos, int chave, int indice)
{  
   BTreeNode *atual = BTreeNode::getNode(this->in, pos);

   int i; //posicao do vetor-chave ou vetor-filhos que a chave deve pertencer
   for (i = 0; i < atual->numChaves && chave > atual->chaves[i]; ++i) 
      {}

   //insere a chave na posicao correta do vetor
   if (atual->isLeaf()) 
   {
      for (int j = atual->numChaves; j > i ; --j)
      {
         atual->chaves[j] = atual->chaves[j - 1];
         atual->indices[j] = atual->indices[j - 1];
      }  
      atual->chaves[i]  = chave;
      atual->indices[i] = indice; 
      ++atual->numChaves;
      atual->setNode(this->out, pos);
   }

   //overflow no No filhos
   else if (insereAux(atual->filhos[i], chave, indice))
   {
      int mediano;
      int posOverflow = i; //index do filho q sofreu overflow
     //
     //
     //
     //
   }
   
   return atual->overflow();
}