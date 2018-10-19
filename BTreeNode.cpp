#include "BTreeNode.hpp"
#include "CabecalhoIndice.hpp"
#include <iostream>
using namespace std;

BTreeNode::BTreeNode (int chave, int indice, int prox)
{
   this->numChaves  = 1;
   this->chaves[0]  = chave;
   this->indices[0] = indice;
   for (int i = 0; i < ORDEM + 1; ++i)
      this->filhos[i] = -1;
   this->prox = prox;
}

BTreeNode::BTreeNode ()
{

}

void BTreeNode::setProx (int prox)
{
   this->prox = prox;
}

int BTreeNode::getProx ()
{
   return this->prox;
}

bool BTreeNode::overflow ()
{
   return (this->numChaves == ORDEM);
}

bool BTreeNode::isLeaf ()
{
   return (this->filhos[0] == -1);
}

BTreeNode* BTreeNode::getNode (std::ifstream &file, int pos)
{
   BTreeNode *node = new BTreeNode();
   file.seekg(sizeof(CabecalhoIndice) + pos * sizeof(BTreeNode));
   file.read((char*)node, sizeof(BTreeNode));
   return node;
}

void BTreeNode::setNode (std::ofstream &file, int pos)
{
   file.seekp(sizeof(CabecalhoIndice) + pos * sizeof(BTreeNode));
   file.write((char*)this, sizeof(BTreeNode));
   file.flush();
}