#include "CabecalhoIndice.hpp"

CabecalhoIndice::CabecalhoIndice ()
{
   this->posRaiz  = -1;
   this->posTopo  =  0;
   this->posLivre = -1; 
}

void CabecalhoIndice::setCabecalho (std::ofstream &file)
{
   file.seekp(0);
   file.write((char*)this, sizeof(CabecalhoIndice));
   file.flush();
}
   
void CabecalhoIndice::setPosRaiz (int posRaiz)
{
   this->posRaiz = posRaiz;
}

void CabecalhoIndice::setPosLivre (int posLivre)
{
   this->posLivre = posLivre;
}

void CabecalhoIndice::incTopo ()
{
   ++this->posTopo;
}

int CabecalhoIndice::getPosRaiz ()
{
   return this->posRaiz;
}

int CabecalhoIndice::getPosLivre ()
{
   return this->posLivre;
}

int CabecalhoIndice::getPosTopo ()
{
   return this->posTopo;
}