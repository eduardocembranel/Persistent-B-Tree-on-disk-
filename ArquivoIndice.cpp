#include <iostream>

#include "ArquivoIndice.hpp"
#include "Util.hpp"

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
   node->setAnt(-1);

   //faz a cabeca antiga apontar para o anterior (nova cabeca)
   if (this->cab->getPosCabeca() != -1)
   {
      BTreeNode *prox = BTreeNode::getNode(this->in, this->cab->getPosCabeca());
      if (this->cab->getPosLivre() == -1)
         prox->setAnt(this->cab->getPosTopo());
      else
         prox->setAnt(this->cab->getPosLivre());
      prox->setNode(this->out, this->cab->getPosTopo());
   }

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
   node->setAnt(-1);

   //faz a cabeca antiga apontar para o anterior (nova cabeca)
   if (this->cab->getPosCabeca() != -1)
   {
      BTreeNode *prox = BTreeNode::getNode(this->in, this->cab->getPosCabeca());
      if (this->cab->getPosLivre() == -1)
         prox->setAnt(this->cab->getPosTopo());
      else
         prox->setAnt(this->cab->getPosLivre());
      prox->setNode(this->out, this->cab->getPosTopo());
   }
   
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

int ArquivoIndice::remove (int chave)
{
   if (this->cab->getPosRaiz() == -1)
      return -1;
   
   int pos = this->removeAux(this->cab->getPosRaiz(), chave);

   BTreeNode *raiz = BTreeNode::getNode(this->in, this->cab->getPosRaiz());
   if (raiz->numChaves == 0)
   {
      int posRaiz = this->cab->getPosRaiz();
      //entao a arvore esta vazia
      if (raiz->isLeaf())
         this->cab->setPosRaiz(-1);
      else
         this->cab->setPosRaiz(raiz->filhos[0]);
      this->removeLista(posRaiz);
   }
   this->cab->setCabecalho(this->out);
   return pos;
}

int ArquivoIndice::removeAux (int pos, int chave)
{
   BTreeNode *atual = BTreeNode::getNode(this->in, pos);   
   
   int i = 0;
   while (i < atual->numChaves && atual->chaves[i] < chave) 
      ++i;

   //chave encontrada
   if (i < atual->numChaves && atual->chaves[i] == chave) 
   { 
      if (atual->isLeaf())
         this->removeDaFolha(pos, i);
      else
         this->removeNaoFolha(pos, i);

      
      return atual->indices[i];
   }

   //chave nao encontrada
   if (atual->isLeaf())
      return -1;

   bool flag = (i == atual->numChaves) ? true : false;

   BTreeNode *filho = BTreeNode::getNode(this->in, atual->filhos[i]);
   
   if (filho->numChaves < 3)
      preenche(pos, i);

   if (flag && i > atual->numChaves)
      return this->removeAux(atual->filhos[i - 1], chave);
   else
      return this->removeAux(atual->filhos[i], chave);
   
}

void ArquivoIndice::removeDaFolha (int pos, int posChave)
{
   BTreeNode *atual = BTreeNode::getNode(this->in, pos);
   
   for (int i = posChave + 1; i < atual->numChaves; ++i) 
   {
      atual->chaves[i - 1]  = atual->chaves[i]; 
      atual->indices[i - 1] = atual->indices[i];
   }
   --atual->numChaves;
   atual->setNode(this->out, pos);
}

void ArquivoIndice::removeNaoFolha (int pos, int posChave)
{
   BTreeNode *atual = BTreeNode::getNode(this->in, pos);
   int chave = atual->chaves[posChave];

   BTreeNode *esq = BTreeNode::getNode(this->in, atual->filhos[posChave]);

   int chaveAnt, indiceAnt;
   this->getAnt(atual->filhos[posChave], chaveAnt, indiceAnt);
   atual->chaves[posChave]  = chaveAnt;
   atual->indices[posChave] = indiceAnt;
   this->removeAux(atual->filhos[posChave], chaveAnt);
   atual->setNode(this->out, pos);
}

void ArquivoIndice::preenche (int pos, int posChave)
{
   BTreeNode *atual = BTreeNode::getNode(this->in, pos);
   BTreeNode *esq   = BTreeNode::getNode(this->in, atual->filhos[posChave - 1]);
   BTreeNode *dir   = BTreeNode::getNode(this->in, atual->filhos[posChave + 1]);

   cout << "teste: " << esq->numChaves << dir->numChaves << "\n";

   cout << "pos chave: " << posChave << " esq: " << esq->numChaves << " dir:" << dir->numChaves << "\n";
   if (posChave != 0 && esq->numChaves > 2)
      this->emprestaEsquerda(pos, posChave);
   else if (posChave != atual->numChaves && dir->numChaves > 2)
      this->emprestaDireita(pos, posChave);
   else
   {
      if (posChave != atual->numChaves)
         this->merge(pos, posChave);
      else
         this->merge(pos, posChave - 1);
   }
}

void  ArquivoIndice::emprestaEsquerda (int pos, int posChave)
{
   BTreeNode *atual = BTreeNode::getNode(this->in, pos);
   BTreeNode *filho = BTreeNode::getNode(this->in, atual->filhos[posChave]);
   BTreeNode *irmao = BTreeNode::getNode(this->in, atual->filhos[posChave - 1]);

   for (int i = filho->numChaves - 1; i >= 0; --i)
   {
      filho->chaves[i + 1]  = filho->chaves[i];
      filho->indices[i + 1] = filho->indices[i];
   } 
   if (!filho->isLeaf())
      for (int i = filho->numChaves; i >= 0; --i)
         filho->filhos[i + 1] = filho->filhos[i];

   filho->chaves[0]  = atual->chaves[posChave - 1];
   filho->indices[0] = atual->indices[posChave - 1];

   if (!filho->isLeaf())
      filho->filhos[0] = irmao->filhos[irmao->numChaves];

   atual->chaves[posChave - 1]  = irmao->chaves[irmao->numChaves -1];
   atual->indices[posChave - 1] = irmao->indices[irmao->numChaves -1];
   ++filho->numChaves;
   --irmao->numChaves;

   atual->setNode(this->out, pos);
   filho->setNode(this->out, atual->filhos[posChave]);
   irmao->setNode(this->out, atual->filhos[posChave - 1]);   
}

void ArquivoIndice::emprestaDireita (int pos, int posChave)
{
   BTreeNode *atual = BTreeNode::getNode(this->in, pos);
   BTreeNode *filho = BTreeNode::getNode(this->in, atual->filhos[posChave]);
   BTreeNode *irmao = BTreeNode::getNode(this->in, atual->filhos[posChave + 1]);

   filho->chaves[filho->numChaves] = atual->chaves[posChave];
   filho->indices[filho->numChaves] = atual->indices[posChave];

   if (!irmao->isLeaf())
      filho->filhos[filho->numChaves + 1] = irmao->filhos[0];

   atual->chaves[posChave]  = irmao->chaves[0];
   atual->indices[posChave] = irmao->indices[0];

   for (int i = 1; i < irmao->numChaves; ++i)
   {
      irmao->chaves[i - 1]  = irmao->chaves[i];
      irmao->indices[i - 1] = irmao->indices[i];
   }
   
   if (!irmao->isLeaf())
      for (int i = 1; i <= irmao->numChaves; ++i)
         irmao->filhos[i - 1] = irmao->filhos[i];

   ++filho->numChaves;
   --irmao->numChaves;
   
   atual->setNode(this->out, pos);
   filho->setNode(this->out, atual->filhos[posChave]);
   irmao->setNode(this->out, atual->filhos[posChave + 1]);
}

void ArquivoIndice::merge (int pos, int posChave)
{
   BTreeNode *atual = BTreeNode::getNode(this->in, pos);
   BTreeNode *filho = BTreeNode::getNode(this->in, atual->filhos[posChave]);
   BTreeNode *irmao = BTreeNode::getNode(this->in, atual->filhos[posChave + 1]);

   //2 = minimo de chaves
   filho->chaves[2]  = atual->chaves[posChave];
   filho->indices[2] = atual->indices[posChave];

   for (int i = 0; i < irmao->numChaves; ++i)
   {
      filho->chaves[i + 2]  = irmao->chaves[i];
      filho->indices[i + 2] = irmao->indices[i];
   }
   if (!filho->isLeaf())
      for (int i = 0; i <= irmao->numChaves; ++i)
         filho->filhos[i + 2] = irmao->filhos[i];
   
   for (int i = posChave + 1; i < atual->numChaves; ++i)
   {
      atual->chaves[i - 1]  = atual->chaves[i];
      atual->indices[i - 1] = atual->indices[i];
   }
   for (int i = posChave + 2; i <= atual->numChaves; ++i)
      atual->filhos[i - 1] = atual->filhos[i];

   filho->numChaves += irmao->numChaves + 1;
   --atual->numChaves;

   atual->setNode(this->out, pos);
   filho->setNode(this->out, atual->filhos[posChave]);
}

void ArquivoIndice::getSuc (int pos, int &chaveSuc, int &indiceSuc) 
{ 
   BTreeNode *atual = BTreeNode::getNode(this->in, pos);
   while (!atual->isLeaf())
      atual = BTreeNode::getNode(this->in, atual->filhos[0]);

   chaveSuc  = atual->chaves[0];
   indiceSuc = atual->indices[0]; 
}

void ArquivoIndice::getAnt (int pos, int &chaveAnt, int &indiceAnt) 
{ 
   BTreeNode *atual = BTreeNode::getNode(this->in, pos);
   while (!atual->isLeaf())
      atual = BTreeNode::getNode(this->in, atual->filhos[atual->numChaves]);

   chaveAnt  = atual->chaves[atual->numChaves - 1];
   indiceAnt = atual->indices[atual->numChaves - 1]; 
} 

void ArquivoIndice::removeLista (int pos)
{
   BTreeNode *atual = BTreeNode::getNode(this->in, pos);

   //remocao na cabeca
   if (pos == this->cab->getPosCabeca())
   {
      this->cab->setPosCabeca(atual->getProx());
      if (atual->getProx() != -1)
      {
         BTreeNode *prox = BTreeNode::getNode(this->in, atual->getProx());
         prox->setAnt(-1);  
         prox->setNode(this->out, atual->getProx());
      }
   }
   //remocao no meio
   else
   {
      //proximo do anterior -> proximo
      BTreeNode *ant = BTreeNode::getNode(this->in, atual->getAnt());
      ant->setProx(atual->getProx());
      ant->setNode(this->out, atual->getAnt());

      //nao eh a calda
      if (atual->getProx() != -1)
      {
         //anterior do proximo -> anterior.
         BTreeNode *prox = BTreeNode::getNode(this->in, atual->getProx());
         prox->setAnt(atual->getAnt());
         prox->setNode(this->out, atual->getProx());
      }
   }
   //Encadeando o No removido na lista de livres
   atual->setProx(this->cab->getPosLivre());
   atual->setAnt(-1);
   atual->setNode(this->out, pos);

   this->cab->setPosLivre(pos);
   this->cab->setCabecalho(this->out);
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
      std::cout << "[";
      for (int i = 0; i < no->numChaves - 1; ++i)
         std::cout << no->chaves[i] << ",";
      std::cout << no->chaves[no->numChaves - 1] << "] ";
   }
   else if (nivel > 1) 
   { 
      for (int i = 0; i <= no->numChaves; ++i)
         mostraNivel(nivel - 1, no->filhos[i]);
   } 
}  

void ArquivoIndice::mostrarPorNivel ()
{
   Util::clear();
   std::cout << "[Arvore B por nivel]\n\n";
   
   int h = this->altura();
   if (h == 0) 
   {
      cout << "Arvore vazia!\n";
   }
   else
   {
      //printa a raiz;
      BTreeNode *no  = BTreeNode::getNode (in, this->cab->getPosRaiz());
      std::cout << "[";
      for (int i = 0; i < no->numChaves - 1; ++i)
         cout << no->chaves[i] << ",";
      cout << no->chaves[no->numChaves - 1] << "]\n";

      for (int i = 2; i <= h; ++i)
      {
         mostraNivel(i, this->cab->getPosRaiz());
         std::cout << "\n";
      }
   }
   Util::pressRetornar();
}

std::vector<int> ArquivoIndice::getIndices ()
{
   std::vector<int> indices;

   if (this->cab->getPosRaiz() != -1)
      getIndicesAux(this->cab->getPosRaiz(), indices);
   
   return indices;
}

void ArquivoIndice::getIndicesAux (int pos, std::vector<int> &indices)
{
   BTreeNode *no = BTreeNode::getNode(this->in, pos);
   
   int i;
   for (i = 0; i < no->numChaves; ++i)
   {
      if (no->isLeaf() == false)
         this->getIndicesAux(no->filhos[i], indices);
      indices.push_back(no->indices[i]);
   }
   if (no->isLeaf() == false)
      this->getIndicesAux(no->filhos[i], indices);

   delete no;
}

int ArquivoIndice::getIndice (int chave)
{
   if (this->cab->getPosRaiz() == -1)
      return -1;

   return getIndiceAux (chave, this->cab->getPosRaiz());
}

int ArquivoIndice::getIndiceAux (int chave, int pos)
{
   if (pos == -1) return -1;

   BTreeNode *no = BTreeNode::getNode(this->in, pos);
   int i = 0;
   while (i < no->numChaves && chave > no->chaves[i])
      ++i;

   if (i < no->numChaves && chave == no->chaves[i]) //achou
      return no->indices[i];

   return getIndiceAux(chave, no->filhos[i]);
}

ArquivoIndice::~ArquivoIndice ()
{
   delete this->cab;
}