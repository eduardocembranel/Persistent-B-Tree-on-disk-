#include "CabecalhoIndice.hpp"

/* brief: construtor da clase: seta os indices do cabecalho
* pre: nenhuma
* pos: cabecalho inicializado
*/
CabecalhoIndice::CabecalhoIndice ()
{
   this->posRaiz   = -1;
   this->posTopo   =  0;
   this->posLivre  = -1; 
}

/* brief: Insere o cabecalho no arquivo binario de dados
* param: buffer para escrita em arquivo
* pre: nenhuma
* pos: cabecalho inserido no arquivo
*/
void CabecalhoIndice::setCabecalho (std::ofstream &file)
{
   file.seekp(0);
   file.write((char*)this, sizeof(CabecalhoIndice));
   file.flush();
}

/* brief: faz o set da posição da raiz
* pre: haver uma raiz
* pos: nenhuma
*/  
void CabecalhoIndice::setPosRaiz (int posRaiz)
{
   this->posRaiz = posRaiz;
}

/* brief: Faz o Set da posição livre
* pre: haver uma raiz
* pos: passagem da proxima posição livre
*/
void CabecalhoIndice::setPosLivre (int posLivre)
{
   this->posLivre = posLivre;
}

/* brief: Aumenta a posição do topo
* pre: haver um topo
* pos: topo ter sido aumentado em 1
*/
void CabecalhoIndice::incTopo ()
{
   ++this->posTopo;
}

/* brief: getter: posRaiz
* pre: nenhuma
* pos: retorna a posicao da raiz
*/
int CabecalhoIndice::getPosRaiz ()
{
   return this->posRaiz;
}

/* brief: getter: posLivre
* pre: nenhuma
* pos: retorna a posicao da cabeca da lista de livres
*/
int CabecalhoIndice::getPosLivre ()
{
   return this->posLivre;
}

/* brief: getter: posTopo
* pre: nenhuma
* pos: retorna a posicao do topo
*/
int CabecalhoIndice::getPosTopo ()
{
   return this->posTopo;
}