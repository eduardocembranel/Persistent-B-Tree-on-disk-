#ifndef CABECALHOINDICE_HPP
#define CABECALHOINDICE_HPP

#include <fstream>

class CabecalhoIndice
{
   private:
      int posRaiz;
      int posLivre;
      int posTopo;

   public:
      CabecalhoIndice ();
      void setCabecalho (std::ofstream &);
      void setPosRaiz (int);
      void setPosLivre (int);
      void incTopo ();
      int getPosRaiz ();
      int getPosLivre ();
      int getPosTopo ();
};

#endif // !CABECALHOINDICE_HPP