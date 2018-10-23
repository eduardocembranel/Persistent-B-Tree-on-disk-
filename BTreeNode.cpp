#include "BTreeNode.hpp"
#include "CabecalhoIndice.hpp"

/* brief: construtor da clase
* param: inteiro com a chave e o indice para criação da arvore
* pre: parametros válidos
* pos: arvore ser criada
*/
BTreeNode::BTreeNode (int chave, int indice)
{
   this->numChaves  = 1;
   this->chaves[0]  = chave;
   this->indices[0] = indice;
   for (int i = 0; i < ORDEM + 1; ++i)
      this->filhos[i] = -1;
}

/* brief: construtor da clase, inicializa com os valores padroes
* pre: nenhum
* pos: arvore ser criada
*/
BTreeNode::BTreeNode ()
{
   for (int i = 0; i < ORDEM + 1; ++i)
      this->filhos[i] = -1;
   this->numChaves = 0;
}

/* brief: Set o proximo nó da lista
* param: inteiro para o proximo nó
* pre: arvore ja implementada
* pos: passar o ponteiro para o proximo nó
*/
void BTreeNode::setProx (int prox)
{
   this->prox = prox;
}

/* brief: Get do proximo nó da lista
* pre: arvore ja implementada
* pos: pegar o proximo nó
*/
int BTreeNode::getProx ()
{
   return this->prox;
}

/* brief: Faz a verificação de excesso de chaves no nó
* pre: nenhuma
* pos: passar se há ou não excesso de chaves
*/
bool BTreeNode::overflow ()
{
   return (this->numChaves == ORDEM);
}

/* brief: Faz a verificação se ha menos chaves que o minimo no nó
* pre: nenhuma
* pos: passar se há ou não menos chaves que o minimo
*/
bool BTreeNode::underflow ()
{
   return (this->numChaves < MINIMO);
}

/* brief: Verifica se o nó é uma folha 
* pre: nenhuma
* pos: passar para a chamada se é ou não uma folha
*/
bool BTreeNode::isLeaf ()
{
   return (this->filhos[0] == -1);
}

/* brief: Get da posição do nó 
* param: um ponteiro para o arquivo e um inteiro para a posição desejada
* pre: nenhuma
* pos: passagem do nó
*/
BTreeNode BTreeNode::getNode (std::ifstream &file, int pos)
{
   BTreeNode node;
   file.seekg(sizeof(CabecalhoIndice) + pos * sizeof(BTreeNode));
   file.read((char*)&node, sizeof(BTreeNode));
   return node;
}

/* brief: Set do nó desejado
* pre: nenhuma
* pos: nó definido 
*/
void BTreeNode::setNode (std::ofstream &file, int pos)
{
   file.seekp(sizeof(CabecalhoIndice) + pos * sizeof(BTreeNode));
   file.write((char*)this, sizeof(BTreeNode));
   file.flush();
}

/* brief: Faz o split em um nó com overflow
* pre: nó ter overflow
* pos: nó dividido em dois
*/
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