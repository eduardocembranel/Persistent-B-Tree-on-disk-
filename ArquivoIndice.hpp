#ifndef ARQUIVOINDICE_HPP
#define ARQUIVOINDICE_HPP

/*
* \file ArquivoIndices.hpp
* \class ArquivoIndices
* \brief Classe que representa o controle de operacoes de um arquivo de indices
* implementado com arvore B
* \author Carlos Pedroso
* \author Eduardo Cembranel
*/

#include <vector>

#include "Arquivo.hpp"
#include "CabecalhoIndice.hpp"
#include "BTreeNode.hpp"

class ArquivoIndice : public Arquivo
{
   private:
      CabecalhoIndice *cab; //cabecalho do arquivo

   public:

      /* brief: construtor da classe, incializa o arquivo de indice
      * param: nome do arquivo de indice
      * pre: nome de arquivo valido
      * pos: arquivo inicializado com cabecalho
      */
      ArquivoIndice (const std::string &);

      /* brief: insere uma chave e indice na arvore b do arquivo de indices
      * pre: chave deve ser um inteiro positivo diferente de zero
      * pos: chave e indice inseridos
      */
      void insere (int, int);

      /* brief: Remove uma chave da arvore B do arquivo de indices, retornando
      * a posicao que esta condido o dado no arquivo de dados
      * param: chave a ser removida
      * return: posicao que esta condido o dado no arquivo de dados
      * pre: nenhuma
      * pos: chave e removida da arvore
      */
      int remove (int);

      /* brief: imprime a arvore por completo por nivel
      * pre: nenhuma
      * pos: arvore exibida caso nao seja vazia
      */
      void mostrarPorNivel ();

      /* brief: obtem a altura da arvore B presente no arquivo
      * return: altura da arovre
      * pre: nenhuma
      * pos: altura retornada
      */
      int altura ();

      /* brief: obtem um indice do arquivo de dados a partir de uma chave da arvore
      * param: chave
      * return: indice do arquivo de dados que relaciona com a chave
      * pre: nenhuma
      * pos: indice obtido
      */
      int getIndice (int);
      
      /* brief: Obtem todos os indices em ordem crescente da posicao dos dados
      * return: vetor de inteiro com os indices ordenados
      * pre: nenhuma
      * pos: indices obtidos
      */
      std::vector<int> getIndices ();
      
      /* brief: destrutor da classe, responsavel por desalocar da memoria o cabecalho 
      * pre: cabecalho alocado
      * pos: cabecalho desalocado
      */
      ~ArquivoIndice ();

   private:

      /* brief: funcao auxiliar do metodo remover que remove uma chave da arvore B
      * param: posicao do No atual e chave a ser removida
      * pre: nenhuma
      * pos: chave removido se presente no No atual
      */
      int removeAux (int, int);

      /* brief: funcao auxiliar que remove uma chave que esta na folha
      * param: posicao do No atual e posicao da chave a ser removida do No
      * pre: chave deve estar contida neste No
      * pos: chave removida
      */
      void removeDaFolha (int, int);

      /* brief: funcao auxiliar que remove uma chave que nao esta na folha
      * removendo tambem recursivamente a chave predecessora
      * param: posicao do No atual e posicao da chave a ser removida do No
      * pre: nenhuma
      * pos: chave removida
      */
      void removeNaoFolha (int, int);

      /* brief: obtem a chave predecessora
      * param: posicao da chave, chaveAnt e indiceAnt serao passados como referencia
      * pre: nenhuma
      * pos: chave e indice predecessor obtidos
      */
      void getAnt (int, int &, int &);

      /* brief: funcao que redistribui as chaves de um No com seu pai e irmao
      * da esquerda para a direita
      * param: posicao do No atual e posicao da chave a ser removida do No
      * pre: nenhuma
      * pos: empreestimo feito
      */
      void emprestaEsquerda (int, int);

      /* brief: funcao que redistribui as chaves de um No com seu pai e irmao
      * da direita para a esquerda
      * param: posicao do No atual e posicao da chave a ser removida do No
      * pre: nenhuma
      * pos: empreestimo feito
      */
      void emprestaDireita (int, int);

      /* brief: intercala dois irmaos com uma chave do No pai
      * da direita para a esquerda
      * param: posicao do No atual e posicao da chave a ser removida do No
      * pre: nenhuma
      * pos: intercalacao efetuada e No irmao removido da arvore
      */
      void mergeDireita (int, int);

      /* brief: intercala dois irmaos com uma chave do No pai
      * da esquerda para a direita
      * param: posicao do No atual e posicao da chave a ser removida do No
      * pre: Apenas pode ser chamada para o caso do No filho mais a direita
      * pos: intercalacao efetuada e No irmao removido da arvore
      */
      void mergeEsquerda (int, int);

      /* brief: Remove um No inteiro da lista duplamente encadeada do arquivo
      * param: posicao do No a ser removido
      * pre: posicao valida
      * pos: No removido e encadeado na lista de Nos livres
      */
      void removeLista (int);

      /* brief: funcao auxiliar para o metodo de inserir chave no arquivo de indices
      * param: posicao do No atual, chave e indice a serem inseridos
      * return: verdadeiro caso ocorreu overflow e falso caso ocorreu underflow
      * pre: chave deve ser um inteiro positivo diferente de zero
      * pos: chave e indice inseridos
      */
      bool insereAux (int, int, int);

      /* brief: insere um No, sendo este a raiz, na lista de Nos do arquivo de indices
      * param: No a ser inserido
      * pre: No deve ser a raiz
      * pos: No inserido no arquivo
      */
      void insereRaiz (BTreeNode);

      /* brief: insere um No na lista de Nos do arquivo de indices
      * param: No a ser inserido
      * return: posicao em que o No foi inserido no arquivo
      * pre: No valido
      * pos: No inserido
      */
      int insereNaoRaiz (BTreeNode);

      /* brief: funcao auxiliar que procura a altura recursivamente, da arvore
      * param: posicao do No atual
      * retorno: 1 e chama recursivamente para o proximo no (caso o atual n for nulo)
      * pre: nenhuma
      * pos: nenhuma
      */
      int alturaAux (int);

      /* brief: imprime na tela as chaves da arvore B de um determinado nivel
      * param: nivel atual e posicao do No atual
      * pre: nivel ser valido
      * pos: chaves exibidas na tela
      */
      void mostraNivel (int, int);

      /* brief: funcao auxiliar para obter os indices em ordem crescente da arvore
      * param: posicao do No atual do no e vetor de indices por referencia
      * pre: nenhuma
      * pos: indice armazenado caso exista no No
      */
      void getIndicesAux (int, std::vector<int> &);

      /* brief: funcao auxiliar que procura pelo indice relacionado a uma chave
      * param: chave e posicao atual
      * return: indice obtido caso a chave esteja no No atual
      * pre: nenhuma
      * pos: nenhuma
      */
      int getIndiceAux (int, int);
};

#endif // !ARQUIVOINDICE_HPP