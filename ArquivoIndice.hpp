#ifndef ARQUIVOINDICE_HPP
#define ARQUIVOINDICE_HPP

#include "Arquivo.hpp"
#include "CabecalhoIndice.hpp"
#include "BTreeNode.hpp"

//insere chave + indice
//arquivo contem BTreeNode
class ArquivoIndice : public Arquivo
{
   private:
      CabecalhoIndice *cab;

   public:
      ArquivoIndice (const std::string &);

      //fazer hoje
      //recebe chave e indice
      void insere (int, int);
      void mostrarPorNivel ();
      int altura();

   private:
      bool insereAux (int, int, int);
      void insereRaiz (BTreeNode*);
      int insereNaoRaiz (BTreeNode*);
      int alturaAux (int);
      void mostraNivel (int, int);
};

#endif // !ARQUIVOINDICE_HPP