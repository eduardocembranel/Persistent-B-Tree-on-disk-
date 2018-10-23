#include "BTreeNode.hpp"
#include "CabecalhoIndice.hpp"

BTreeNode::BTreeNode (int chave, int indice)
{
   this->numChaves  = 1;
   this->chaves[0]  = chave;
   this->indices[0] = indice;
   for (int i = 0; i < ORDEM + 1; ++i)
      this->filhos[i] = -1;
}

BTreeNode::BTreeNode ()
{
   for (int i = 0; i < ORDEM + 1; ++i)
      this->filhos[i] = -1;
   this->numChaves = 0;
}

void BTreeNode::setProx (int prox)
{
   this->prox = prox;
}

int BTreeNode::getProx ()
{
   return this->prox;
}

int BTreeNode::getAnt ()
{
   return this->ant;
}

void BTreeNode::setAnt (int ant)
{
   this->ant = ant;
}

bool BTreeNode::overflow ()
{
   return (this->numChaves == ORDEM);
}

bool BTreeNode::underflow ()
{
   return (this->numChaves < MINIMO);
}

bool BTreeNode::isLeaf ()
{
   return (this->filhos[0] == -1);
}

BTreeNode BTreeNode::getNode (std::ifstream &file, int pos)
{
   BTreeNode node;
   file.seekg(sizeof(CabecalhoIndice) + pos * sizeof(BTreeNode));
   file.read((char*)&node, sizeof(BTreeNode));
   return node;
}

void BTreeNode::setNode (std::ofstream &file, int pos)
{
   file.seekp(sizeof(CabecalhoIndice) + pos * sizeof(BTreeNode));
   file.write((char*)this, sizeof(BTreeNode));
   file.flush();
}

BTreeNode BTreeNode::split (BTreeNode &node, int *medChave, int *medIndice)
{
   BTreeNode novo;
   int posMed = 2; // -> numChave / 2
   int i, j, fim = node.numChaves;

   for (i = posMed + 1, j = 0; i < fim; ++i, ++j)
   {
      novo.filhos[j]  = node.filhos[i];
      novo.chaves[j]  = node.chaves[i];
      novo.indices[j] = node.indices[i];
      node.filhos[i]  = -1;
      ++novo.numChaves;
      --node.numChaves;
   }

   novo.filhos[j] = node.filhos[i];
   node.filhos[i] = -1;
   *medChave  = node.chaves[posMed];
   *medIndice = node.indices[posMed];
   --node.numChaves;

   return novo;
}