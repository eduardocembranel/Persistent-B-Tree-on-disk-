#include <cstdio>

#include "CabecalhoDados.hpp"

/* brief: construtor da clase: seta os indices do cabecalho
* pre: nenhuma
* pos: cabecalho inicializado
*/
CabecalhoDados::CabecalhoDados ()
{
   this->posTopo   =  0;
   this->posLivre  = -1;
}

/* brief: Insere o cabecalho no arquivo binario de dados
* param: buffer para escrita em arquivo
* pre: nenhuma
* pos: cabecalho inserido no arquivo
*/
void CabecalhoDados::setCabecalho (std::ofstream &file)
{
   file.seekp(0);
   file.write((char*)this, sizeof(CabecalhoDados));
   file.flush();
}

/* brief: Faz o Get da posição do topo
* pre: haver uma no topo
* pos: passagem da posição no topo da arvore
*/
int CabecalhoDados::getPosTopo ()
{
   return this->posTopo;
}

/* brief: Faz o Get da proxima posição livre
* pre: haver uma raiz
* pos: passagem da proxima posição livre
*/
int CabecalhoDados::getPosLivre ()
{
   return this->posLivre;
}

/* brief: setter
* param: inteiro com a posicao
* pre: parametros válidos
*/
void CabecalhoDados::setPosLivre (int x)
{
   this->posLivre = x;
}

/* brief: Aumenta a posição do topo
* pre: haver um topo
* pos: topo ter sido aumentado em 1
*/
void CabecalhoDados::incTopo ()
{
   ++this->posTopo;
}