#include <fstream>

#include "ArquivoDados.hpp"

/* brief: construtor: inicializa o arquivo e cabecalho do arquivo
* pre: nenhuma
* pos: arquivo e cabecalho inicializados 
*/
ArquivoDados::ArquivoDados (const std::string &fileName) : Arquivo(fileName)
{  
   this->cab = new CabecalhoDados();
   this->cab->setCabecalho(this->out); //coloca o cabecalho no arquivo
}

/* brief: Faz a inserção de um médico na arvore
* pre: arvore ja ter sido criada
* pos: o dado ter sido inserido na arvore
*/
int ArquivoDados::insere (Medico medico)
{
   int indice;
   NoMedico x;
   x.setMedico(medico);
   
   //nao ha nós livres
   if (this->cab->getPosLivre() == -1)
   {
      indice = this->cab->getPosTopo();
      this->insereNo(&x, indice);
      this->cab->incTopo();
   }
   else
   {
      indice = this->cab->getPosLivre();
      NoMedico aux = this->getData(indice);
      this->insereNo(&x, indice);
      this->cab->setPosLivre(aux.getProx());
   }
   this->cab->setCabecalho(this->out);
   return indice;
}

/* brief: Faz a inserção de um novo nó na arvore
* param: ponteiro para o elemento a ser inserido e a posição
* pre: a arvore não estar vazia
* pos: ter inserido o nó
*/
void ArquivoDados::insereNo (NoMedico *elem, int pos)
{
   this->out.seekp(sizeof(CabecalhoDados) + pos * sizeof(NoMedico));
   this->out.write((char*)elem, sizeof(NoMedico));
   this->out.flush();
}

/* brief: Faz a remoção de um nó
* param:  a posição a ser removida
* pre: haver uma arvore
* pos: o elemento ter sido removido
*/
void ArquivoDados::remove (int pos)
{
   NoMedico atual = this->getData(pos);

   //Encadeando o No removido na lista de livres
   atual.setProx(this->cab->getPosLivre());
   this->cab->setPosLivre(pos);
   this->insereNo(&atual, pos);
   
   this->cab->setCabecalho(this->out);
}

/* brief: Recolhe os dados do médico
* pre: nenhum
* pos: retorna os dados 
*/
NoMedico ArquivoDados::getData (int pos)
{
   NoMedico x;
   this->in.seekg(sizeof(CabecalhoDados) + pos * sizeof(NoMedico));
   this->in.read((char*)&x, sizeof(NoMedico));
   return x;
}

/* brief: destrutor: desaloca memoria do cabecalho do arquivo
* pre: cabecalho alocado
* pos: cabecalho desalocado 
*/
ArquivoDados::~ArquivoDados ()
{
   delete this->cab;
}