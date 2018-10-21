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
      int remove (int);
      void mostrarPorNivel ();
      int altura ();
      int getIndice (int); //dada uma chave
      std::vector<int> getIndices ();
      ~ArquivoIndice ();

   private:
      int removeAux (int, int);
      void removeDaFolha (int, int);
      void removeNaoFolha (int, int);
      void getSuc (int, int &, int &);
      void getAnt (int, int &, int &);
      void preenche (int, int);
      void emprestaEsquerda (int, int);
      void emprestaDireita (int, int);
      void merge (int, int);
      void removeLista (int);
      bool insereAux (int, int, int);
      void insereRaiz (BTreeNode*);
      int insereNaoRaiz (BTreeNode*);
      int alturaAux (int);
      void mostraNivel (int, int);
      void getIndicesAux (int, std::vector<int> &);
      int getIndiceAux (int, int);
};

#endif // !ARQUIVOINDICE_HPP