#ifndef BTREENODE_HPP
#define BTREENODE_HPP

/*
* \file BTreeNode.hpp
* \class BTreeNode
* \brief Classe que representa um nó de arvore B
*  para implementacao em arquivo binario com lista duplamente encadeada
* \author Carlos Pedroso
* \author Eduardo Cembranel
*/

#include <fstream>

class BTreeNode
{
   friend class ArquivoIndice;
   
   private:
      static const int ORDEM  = 5;
      static const int MINIMO = 2;
      int numChaves;
      int chaves[ORDEM];
      int filhos[ORDEM + 1];
      int indices[ORDEM];
      int prox;

      /* brief: construtor da clase
      * param: inteiro com a chave e o indice para criação da arvore
      * pre: parametros válidos
      * pos: arvore ser criada
      */
      BTreeNode (int, int);

      /* brief: construtor da clase, inicializa com os valores padroes
      * pre: nenhum
      * pos: arvore ser criada
      */
      BTreeNode ();

      /* brief: Set o proximo nó da lista
      * param: inteiro para o proximo nó
      * pre: arvore ja implementada
      * pos: passar o ponteiro para o proximo nó
      */
      void setProx (int);

      /* brief: Get do proximo nó da lista
      * pre: arvore ja implementada
      * pos: pegar o proximo nó
      */
      int getProx ();

      /* brief: Faz a verificação de excesso de chaves no nó
      * pre: nenhuma
      * pos: passar se há ou não excesso de chaves
      */
      bool overflow ();

      /* brief: Faz a verificação se ha menos chaves que o minimo no nó
      * pre: nenhuma
      * pos: passar se há ou não menos chaves que o minimo
      */
      bool underflow ();

      /* brief: Verifica se o nó é uma folha 
      * pre: nenhuma
      * pos: passar para a chamada se é ou não uma folha
      */
      bool isLeaf ();

      /* brief: Set do nó desejado
      * pre: nenhuma
      * pos: nó definido 
      */
      void setNode (std::ofstream &, int);

      /* brief: Get da posição do nó 
      * param: um ponteiro para o arquivo e um inteiro para a posição desejada
      * pre: nenhuma
      * pos: passagem do nó
      */
      static BTreeNode getNode (std::ifstream &, int);

      /* brief: Faz o split em um nó com overflow
      * pre: nó ter overflow
      * pos: nó dividido em dois
      */
      static BTreeNode split (BTreeNode &, int *, int *);

};

#endif // !BTREENODE_HPP