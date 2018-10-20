#ifndef ARQUIVOINDICE_HPP
#define ARQUIVOINDICE_HPP

#include "Arquivo.hpp"
#include "CabecalhoIndice.hpp"
#include "BTreeNode.hpp"

#include <vector>

//insere chave + indice
//arquivo contem BTreeNode
class ArquivoIndice : public Arquivo
{
   private:
      CabecalhoIndice *cab;

   public:
      ArquivoIndice (const std::string &);

      void insere (int, int);
      void mostrarPorNivel ();
      int altura ();
      int getIndice (int); //dada uma chave
      std::vector<int> getIndices ();
      ~ArquivoIndice ();

   private:
      bool insereAux (int, int, int);
      void insereRaiz (BTreeNode*);
      int insereNaoRaiz (BTreeNode*);
      int alturaAux (int);
      void mostraNivel (int, int);
      void getIndicesAux (int, std::vector<int> &);
      int getIndiceAux (int, int);
};

#endif // !ARQUIVOINDICE_HPP