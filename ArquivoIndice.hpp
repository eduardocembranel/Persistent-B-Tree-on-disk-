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
};

#endif // !ARQUIVOINDICE_HPP