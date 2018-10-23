#ifndef ARQUIVODADOS_HPP
#define ARQUIVODADOS_HPP

/*
* \file ArquivoDados.hpp
* \class ArquivoDados
* \brief Classe que representa o controle de operacoes de um arquivo de dados
* \author Carlos Pedroso
* \author Eduardo Cembranel
*/

#include <string>

#include "Arquivo.hpp"
#include "CabecalhoDados.hpp"

class ArquivoDados : public Arquivo
{
   private:
      CabecalhoDados *cab; //cabecalho do arquivo

   public:
      /* brief: construtor: inicializa o arquivo e cabecalho do arquivo
      * pre: nenhuma
      * pos: arquivo e cabecalho inicializados 
      */
      ArquivoDados (const std::string&);

      /* brief: Faz a inserção de um médico na arvore
      * pre: arvore ja ter sido criada
      * pos: o dado ter sido inserido na arvore
      */
      int insere (Medico);

      /* brief: Faz a remoção de um nó
      * param:  a posição a ser removida
      * pre: haver uma arvore
      * pos: o elemento ter sido removido
      */
      void remove (int);

      /* brief: Faz a inserção de um novo nó na arvore
      * param: ponteiro para o elemento a ser inserido e a posição
      * pre: a arvore não estar vazia
      * pos: ter inserido o nó
      */
      void insereNo (NoMedico*, int);

      /* brief: Recolhe os dados do médico
      * pre: nenhum
      * pos: retorna os dados 
      */
      NoMedico getData (int);

      /* brief: destrutor: desaloca memoria do cabecalho do arquivo
      * pre: cabecalho alocado
      * pos: cabecalho desalocado 
      */
      ~ArquivoDados ();
      
   private:
      
};

#endif // !ARQUIVODADOS_HPP