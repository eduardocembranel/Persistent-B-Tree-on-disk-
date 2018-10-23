#ifndef CABECALHODADOS_HPP
#define CABECALHODADOS_HPP

/*
* \file CabecalhoDados.hpp
* \class CabecalhoDados
* \brief Classe que representa o cabecalho de um arquivo de dados
* \author Carlos Pedroso
* \author Eduardo Cembranel
*/

#include <cstdio>
#include <string>
#include <fstream>

class CabecalhoDados
{
   private:
      int posTopo;
      int posLivre;

   public:

      /* brief: construtor da clase: seta os indices do cabecalho
      * pre: nenhuma
      * pos: cabecalho inicializado
      */
      CabecalhoDados ();

      /* brief: Insere o cabecalho no arquivo binario de dados
      * param: buffer para escrita em arquivo
      * pre: nenhuma
      * pos: cabecalho inserido no arquivo
      */
      void setCabecalho (std::ofstream&);

      /* brief: Faz o Get da proxima posição livre
      * pre: haver uma raiz
      * pos: passagem da proxima posição livre
      */
      int getPosLivre ();

      /* brief: setter
      * param: inteiro com a posicao
      * pre: parametros válidos
      */
      void setPosLivre (int);

      /* brief: Faz o Get da posição do topo
      * pre: haver uma no topo
      * pos: passagem da posição no topo da arvore
      */
      int getPosTopo ();

      /* brief: Aumenta a posição do topo
      * pre: haver um topo
      * pos: topo ter sido aumentado em 1
      */
      void incTopo ();
};

#endif // !CABECALHODADOS_HPP