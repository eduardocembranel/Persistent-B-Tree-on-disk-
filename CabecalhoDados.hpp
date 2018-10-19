#ifndef CABECALHODADOS_HPP
#define CABECALHODADOS_HPP

#include <cstdio>
#include <string>
#include <fstream>

class CabecalhoDados
{
   private:
      int posCabeca;
      int posTopo;
      int posLivre;

   public:
      CabecalhoDados ();
      CabecalhoDados* getCabecalho (std::ifstream&);
      void setCabecalho (std::ofstream&);
      int getPosCabeca ();
      int getPosTopo ();
      int getPosLivre ();
      void setPosCabeca (int);
      void setPosLivre (int);
      void incTopo ();
};

#endif // !CABECALHODADOS_HPP