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
      BTreeNode *raiz = new BTreeNode(chave, indice);
      insereRaiz(raiz);
   }
   else if (insereAux(this->cab->getPosRaiz(), chave, indice) == true) //insere e se deu overflow
   {
      int medChave, medIndice;
      BTreeNode *raiz = BTreeNode::getNode(this->in, this->cab->getPosRaiz());
      BTreeNode *novo = BTreeNode::split(raiz, &medChave, &medIndice);

      raiz->setNode(this->out, this->cab->getPosRaiz()); //recoloca a raiz antiga
      int posNovo = insereNaoRaiz(novo); //coloca o novo No (lado direito)
   
      BTreeNode *novaRaiz = new BTreeNode(medChave, medIndice); //2 = prox???
      novaRaiz->filhos[0] = this->cab->getPosRaiz(); //criar um construtor q inicializa os 2 filhos dps
      novaRaiz->filhos[1] = posNovo;                 /////////////
      insereRaiz(novaRaiz);      
   }
   this->cab->setCabecalho(this->out); //precisa setar antes ou so no final?
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
      int medChave, medIndice;
      int posOverflow = i; //index do filho q sofreu overflow
      BTreeNode *cheio = BTreeNode::getNode(this->in, atual->filhos[i]);
      BTreeNode *novo  = BTreeNode::split(cheio, &medChave, &medIndice);

      //insere de volta o antigo No cheio
      cheio->setNode(this->out, atual->filhos[i]);

      //inserir o mediano na posicao correta
      for (i = 0; i < atual->numChaves && medChave > atual->chaves[i]; ++i)
      {}
      for (int j = atual->numChaves; j > i ; --j)
      {
         atual->chaves[j]  = atual->chaves[j - 1];
         atual->indices[j] = atual->indices[j - 1];
      }
      atual->chaves[i]  = medChave;
      atual->indices[i] = medIndice;
      ++atual->numChaves;

      //inserir o novo No filho na posicao correta
      int j;
      for (j = atual->numChaves; j > posOverflow + 1; --j)
         atual->filhos[j] = atual->filhos[j - 1];

      int posNovo = insereNaoRaiz(novo);
      atual->filhos[j] = posNovo;
      atual->setNode(this->out, pos);
   }
   
   return atual->overflow();
}

void ArquivoIndice::insereRaiz (BTreeNode *node)
{
   node->setProx(this->cab->getPosCabeca());
   if (this->cab->getPosLivre() == -1)
   {
      node->setNode(this->out, this->cab->getPosTopo());
      this->cab->setPosRaiz(this->cab->getPosTopo());
      this->cab->setPosCabeca(this->cab->getPosTopo());
      this->cab->incTopo();
   }
   else
   {
      BTreeNode *aux = BTreeNode::getNode(this->in, this->cab->getPosLivre());
      node->setNode(this->out, this->cab->getPosLivre());
      this->cab->setPosRaiz(this->cab->getPosLivre());
      this->cab->setPosCabeca(this->cab->getPosLivre());
      this->cab->setPosLivre(aux->getProx());
      delete aux;
   }
}

int ArquivoIndice::insereNaoRaiz (BTreeNode *node)
{
   int pos;
   node->setProx(this->cab->getPosCabeca());
   if (this->cab->getPosLivre() == -1)
   {
      pos = this->cab->getPosTopo();
      this->cab->setPosCabeca(pos);
      node->setNode(this->out, pos);
      this->cab->incTopo();
      return pos;
   }
   pos = this->cab->getPosLivre();
   this->cab->setPosCabeca(pos);
   BTreeNode *aux = BTreeNode::getNode(this->in, pos);
   node->setNode(this->out, pos);
   this->cab->setPosLivre(aux->getProx());
   delete aux;
   return pos;
}

int ArquivoIndice::altura ()
{
   if (this->cab->getPosRaiz() == -1)
      return 0;

   BTreeNode *raiz = BTreeNode::getNode(this->in, this->cab->getPosRaiz());   
   return this->alturaAux(raiz->filhos[0]);
}

int ArquivoIndice::alturaAux (int pos)
{
   if (pos == -1) return 1;

   BTreeNode *no = BTreeNode::getNode(this->in, pos);   
   return 1 + this->alturaAux(no->filhos[0]);
}

void ArquivoIndice::mostraNivel (int nivel, int pos)
{
   BTreeNode *no = BTreeNode::getNode(this->in, pos);

   if (nivel == 1)
   {
      for (int i = 0; i < no->numChaves; ++i)
         std::cout << "[" << no->chaves[i] << "]";
      std::cout << "  ";
   }
   else if (nivel > 1) 
   { 
      for (int i = 0; i <= no->numChaves; ++i)
         mostraNivel(nivel - 1, no->filhos[i]);
   } 
}  

void ArquivoIndice::mostrarPorNivel ()
{
   int h = this->altura();

   if (h == 0) 
   {
      cout << "VAZIA\n";
      return;
   }

   //printa a raiz;
   BTreeNode *no1  = BTreeNode::getNode (in, this->cab->getPosRaiz());
   for (int i = 0; i < no1->numChaves; ++i)
      cout << "[" << no1->chaves[i] << "]";
   cout << "\n";

   for (int i = 2; i <= h; ++i)
   { 
      mostraNivel(i, this->cab->getPosRaiz());
      std::cout << "\n";
   }
}
