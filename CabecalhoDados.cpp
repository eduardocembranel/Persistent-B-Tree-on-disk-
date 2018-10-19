#include <cstdio>

#include "CabecalhoDados.hpp"

CabecalhoDados::CabecalhoDados ()
{
   this->posCabeca = -1;
   this->posTopo   =  0;
   this->posLivre  = -1;
}

CabecalhoDados* CabecalhoDados::getCabecalho (std::ifstream &file)
{
   CabecalhoDados *cab;
   file.seekg(0);
   file.read((char*)cab, sizeof(CabecalhoDados));
   return cab;
}

void CabecalhoDados::setCabecalho (std::ofstream &file)
{
   file.seekp(0);
   file.write((char*)this, sizeof(CabecalhoDados));
   file.flush();
}

int CabecalhoDados::getPosCabeca ()
{
   return this->posCabeca;
}

int CabecalhoDados::getPosTopo ()
{
   return this->posTopo;
}

int CabecalhoDados::getPosLivre ()
{
   return this->posLivre;
}

void CabecalhoDados::setPosCabeca (int x)
{
   this->posCabeca = x;
}

void CabecalhoDados::setPosLivre (int x)
{
   this->posLivre = x;
}

void CabecalhoDados::incTopo ()
{
   ++this->posTopo;
}