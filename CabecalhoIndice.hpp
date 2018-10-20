#ifndef CABECALHOINDICE_HPP
#define CABECALHOINDICE_HPP

#include <fstream>

class CabecalhoIndice
{
   private:
      int posRaiz;
      int posLivre;
      int posTopo;
      int posCabeca;

   public:
      CabecalhoIndice ();
      void setCabecalho (std::ofstream &);
      void setPosRaiz (int);
      void setPosLivre (int);
      void setPosCabeca (int);
      void incTopo ();
      int getPosRaiz ();
      int getPosLivre ();
      int getPosTopo ();
      int getPosCabeca ();
};

#endif // !CABECALHOINDICE_HPP