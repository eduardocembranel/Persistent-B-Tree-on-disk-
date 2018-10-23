#ifndef CABECALHOINDICE_HPP
#define CABECALHOINDICE_HPP

/*
* \file CabecalhoIndice.hpp
* \class CabecalhoIndice
* \brief Classe que representa o cabecalho de um arquivo de indices
* \author Carlos Pedroso
* \author Eduardo Cembranel
*/

#include <fstream>

class CabecalhoIndice
{
   private:
      int posRaiz;
      int posLivre;
      int posTopo;

   public:

      /* brief: construtor da clase: seta os indices do cabecalho
      * pre: nenhuma
      * pos: cabecalho inicializado
      */
      CabecalhoIndice ();

      /* brief: Insere o cabecalho no arquivo binario de dados
      * param: buffer para escrita em arquivo
      * pre: nenhuma
      * pos: cabecalho inserido no arquivo
      */
      void setCabecalho (std::ofstream &);

      /* brief: faz o set da posição da raiz
      * pre: haver uma raiz
      * pos: nenhuma
      */ 
      void setPosRaiz (int);

      /* brief: Faz o Set da posição livre
      * pre: haver uma raiz
      * pos: passagem da proxima posição livre
      */
      void setPosLivre (int);

      /* brief: Aumenta a posição do topo
      * pre: haver um topo
      * pos: topo ter sido aumentado em 1
      */
      void incTopo ();

      /* brief: getter: posRaiz
      * pre: nenhuma
      * pos: retorna a posicao da raiz
      */
      int getPosRaiz ();

      /* brief: getter: posLivre
      * pre: nenhuma
      * pos: retorna a posicao da cabeca da lista de livres
      */
      int getPosLivre ();

      /* brief: getter: posTopo
      * pre: nenhuma
      * pos: retorna a posicao do topo
      */
      int getPosTopo ();
};

#endif // !CABECALHOINDICE_HPP