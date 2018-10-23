#include <iostream>

#include "ArquivoIndice.hpp"
#include "Util.hpp"

/* brief: construtor da classe, incializa o arquivo de indice
* param: nome do arquivo de indice
* pre: nome de arquivo valido
* pos: arquivo inicializado com cabecalho
*/
ArquivoIndice::ArquivoIndice (const std::string &fileName) : Arquivo(fileName)
{  
   this->cab = new CabecalhoIndice();
   this->cab->setCabecalho(this->out); //coloca o cabecalho no arquivo
}

/* brief: insere uma chave e indice na arvore b do arquivo de indices
* pre: chave deve ser um inteiro positivo diferente de zero
* pos: chave e indice inseridos
*/
void ArquivoIndice::insere (int chave, int indice)
{
   //arvore vazia
   if (this->cab->getPosRaiz() == -1)
   {
      BTreeNode raiz(chave, indice);
      insereRaiz(raiz);
   }
   //insere e se deu overflow
   else if (insereAux(this->cab->getPosRaiz(), chave, indice) == true)
   {
      int medChave, medIndice;
      BTreeNode raiz = BTreeNode::getNode(this->in, this->cab->getPosRaiz());
      BTreeNode novo = BTreeNode::split(raiz, &medChave, &medIndice);

      raiz.setNode(this->out, this->cab->getPosRaiz()); //recoloca a raiz antiga
      int posNovo = insereNaoRaiz(novo); //coloca o novo No (direito dosplit)
   
      BTreeNode novaRaiz(medChave, medIndice);
      novaRaiz.filhos[0] = this->cab->getPosRaiz();
      novaRaiz.filhos[1] = posNovo;         
      insereRaiz(novaRaiz);      
   }
   this->cab->setCabecalho(this->out);
}

/* brief: funcao auxiliar para o metodo de inserir chave no arquivo de indices
* param: posicao do No atual, chave e indice a serem inseridos
* return: verdadeiro caso ocorreu overflow e falso caso ocorreu underflow
* pre: chave deve ser um inteiro positivo diferente de zero
* pos: chave e indice inseridos
*/
bool ArquivoIndice::insereAux (int pos, int chave, int indice)
{  
   BTreeNode atual = BTreeNode::getNode(this->in, pos);

   int i; //posicao do vetor-chave ou vetor-filhos que a chave deve pertencer
   for (i = 0; i < atual.numChaves && chave > atual.chaves[i]; ++i) 
      {}

   //insere a chave na posicao correta do vetor
   if (atual.isLeaf()) 
   {
      for (int j = atual.numChaves; j > i ; --j)
      {
         atual.chaves[j] = atual.chaves[j - 1];
         atual.indices[j] = atual.indices[j - 1];
      }  
      atual.chaves[i]  = chave;
      atual.indices[i] = indice; 
      ++atual.numChaves;
      atual.setNode(this->out, pos);
   }

   //overflow no No filhos
   else if (insereAux(atual.filhos[i], chave, indice))
   {
      int medChave, medIndice;
      int posOverflow = i; //index do filho q sofreu overflow
      BTreeNode cheio = BTreeNode::getNode(this->in, atual.filhos[i]);
      BTreeNode novo  = BTreeNode::split(cheio, &medChave, &medIndice);

      //insere de volta o antigo No cheio
      cheio.setNode(this->out, atual.filhos[i]);

      //inserir o mediano na posicao correta
      for (i = 0; i < atual.numChaves && medChave > atual.chaves[i]; ++i)
      {}
      for (int j = atual.numChaves; j > i ; --j)
      {
         atual.chaves[j]  = atual.chaves[j - 1];
         atual.indices[j] = atual.indices[j - 1];
      }
      atual.chaves[i]  = medChave;
      atual.indices[i] = medIndice;
      ++atual.numChaves;

      //inserir o novo No filho na posicao correta
      int j;
      for (j = atual.numChaves; j > posOverflow + 1; --j)
         atual.filhos[j] = atual.filhos[j - 1];

      int posNovo = insereNaoRaiz(novo);
      atual.filhos[j] = posNovo;
      atual.setNode(this->out, pos);
   }
   return atual.overflow();
}

/* brief: insere um No, sendo este a raiz, na lista de Nos do arquivo de indices
* param: No a ser inserido
* pre: No deve ser a raiz
* pos: No inserido no arquivo
*/
void ArquivoIndice::insereRaiz (BTreeNode node)
{
   if (this->cab->getPosLivre() == -1)
   {
      node.setNode(this->out, this->cab->getPosTopo());
      this->cab->setPosRaiz(this->cab->getPosTopo());
      this->cab->incTopo();
   }
   else
   {  
      BTreeNode aux = BTreeNode::getNode(this->in, this->cab->getPosLivre());
      node.setNode(this->out, this->cab->getPosLivre());
      this->cab->setPosRaiz(this->cab->getPosLivre());
      this->cab->setPosLivre(aux.getProx());
   }
}

/* brief: insere um No na lista de Nos do arquivo de indices
* param: No a ser inserido
* return: posicao em que o No foi inserido no arquivo
* pre: No valido
* pos: No inserido
*/
int ArquivoIndice::insereNaoRaiz (BTreeNode node)
{
   int pos;
   
   if (this->cab->getPosLivre() == -1)
   {
      pos = this->cab->getPosTopo();
      node.setNode(this->out, pos);
      this->cab->incTopo();
      return pos;
   }
   pos = this->cab->getPosLivre();
   BTreeNode aux = BTreeNode::getNode(this->in, pos);
   node.setNode(this->out, pos);
   this->cab->setPosLivre(aux.getProx());
   return pos;
}

/* brief: Remove uma chave da arvore B do arquivo de indices, retornando
* a posicao que esta condido o dado no arquivo de dados
* param: chave a ser removida
* return: posicao que esta condido o dado no arquivo de dados
* pre: nenhuma
* pos: chave e removida da arvore
*/
int ArquivoIndice::remove (int chave)
{
   if (this->cab->getPosRaiz() == -1)
      return -1;
   
   int pos = this->removeAux(this->cab->getPosRaiz(), chave);

   BTreeNode raiz = BTreeNode::getNode(this->in, this->cab->getPosRaiz());

   //CASO 4: raiz vazia
   if (raiz.numChaves == 0)
   {
      int posRaiz = this->cab->getPosRaiz();
      if (raiz.isLeaf())   
         this->cab->setPosRaiz(-1);
      else
         this->cab->setPosRaiz(raiz.filhos[0]);
      this->removeLista(posRaiz);
   }
   this->cab->setCabecalho(this->out);
   return pos;
}

/* brief: funcao auxiliar do metodo remover que remove uma chave da arvore B
* param: posicao do No atual e chave a ser removida
* pre: nenhuma
* pos: chave removido se presente no No atual
*/
int ArquivoIndice::removeAux (int pos, int chave)
{
   BTreeNode atual = BTreeNode::getNode(this->in, pos);   

   int i = 0;
   while (i < atual.numChaves && chave > atual.chaves[i])
      ++i;
   int retorno = atual.indices[i];
   //chave encontrada
   if (i < atual.numChaves && atual.chaves[i] == chave) 
   { 
      if (atual.isLeaf())
         this->removeDaFolha(pos, i);
      else
         this->removeNaoFolha(pos, i);
   }
   else
   {
      //chave nao encontrada
      if (atual.isLeaf())
         return -1;

      retorno = removeAux(atual.filhos[i], chave);
   }
   if (atual.isLeaf())
      return retorno;

   //tratamento de underflow
   BTreeNode filho = BTreeNode::getNode(this->in, atual.filhos[i]);
   if (filho.underflow())
   {
      //nao possui irmao a esquerda
      if (i == 0)
      {
         BTreeNode dir = BTreeNode::getNode(this->in, atual.filhos[i + 1]);
         
         //redistribui com a direita
         if (dir.numChaves > dir.MINIMO)
            emprestaDireita(pos, i);

         //concatena com a direita
         else
            mergeDireita(pos, i);
      }
      //n possui irmao a direita
      else if (i == atual.numChaves)
      {
         BTreeNode esq = BTreeNode::getNode(this->in, atual.filhos[i - 1]);
         
         //redistribui com a esquerda
         if (esq.numChaves > esq.MINIMO)
            emprestaEsquerda(pos, i);
   
         //concatena com a esquerda
         else
            mergeEsquerda(pos, i);
      }
      //possui 2 irmaos adjacentes
      else
      {
         BTreeNode esq = BTreeNode::getNode(this->in, atual.filhos[i - 1]);
         
         //redistribui com a esquerda
         if (esq.numChaves > esq.MINIMO)
            emprestaEsquerda(pos, i);
         else
         {
            BTreeNode dir = BTreeNode::getNode(this->in, atual.filhos[i + 1]);
            //redistribui com a direita
            if (dir.numChaves > dir.MINIMO)
               emprestaDireita(pos, i);
            else
               mergeDireita(pos, i);
         }
      }
   }
   return retorno;
}

/* brief: funcao auxiliar que remove uma chave que esta na folha
* param: posicao do No atual e posicao da chave a ser removida do No
* pre: chave deve estar contida neste No
* pos: chave removida
*/
void ArquivoIndice::removeDaFolha (int pos, int posChave)
{
   BTreeNode atual = BTreeNode::getNode(this->in, pos);
   
   for (int i = posChave + 1; i < atual.numChaves; ++i) 
   {
      atual.chaves[i - 1]  = atual.chaves[i]; 
      atual.indices[i - 1] = atual.indices[i];
   }
   --atual.numChaves;
   atual.setNode(this->out, pos);
}

/* brief: funcao auxiliar que remove uma chave que nao esta na folha
* removendo tambem recursivamente a chave predecessora
* param: posicao do No atual e posicao da chave a ser removida do No
* pre: nenhuma
* pos: chave removida
*/
void ArquivoIndice::removeNaoFolha (int pos, int posChave)
{
   BTreeNode atual = BTreeNode::getNode(this->in, pos);
   int chave = atual.chaves[posChave];

   BTreeNode esq = BTreeNode::getNode(this->in, atual.filhos[posChave]);

   int chaveAnt, indiceAnt;
   this->getAnt(atual.filhos[posChave], chaveAnt, indiceAnt);
   atual.chaves[posChave]  = chaveAnt;
   atual.indices[posChave] = indiceAnt;
   this->removeAux(atual.filhos[posChave], chaveAnt);

   atual.setNode(this->out, pos);
}

/* brief: funcao que redistribui as chaves de um No com seu pai e irmao
* da esquerda para a direita
* param: posicao do No atual e posicao da chave a ser removida do No
* pre: nenhuma
* pos: empreestimo feito
*/
void  ArquivoIndice::emprestaEsquerda (int pos, int posChave)
{
   BTreeNode atual = BTreeNode::getNode(this->in, pos);
   BTreeNode filho = BTreeNode::getNode(this->in, atual.filhos[posChave]);
   BTreeNode irmao = BTreeNode::getNode(this->in, atual.filhos[posChave - 1]);

   for (int i = filho.numChaves - 1; i >= 0; --i)
   {
      filho.chaves[i + 1]  = filho.chaves[i];
      filho.indices[i + 1] = filho.indices[i];
   } 
   if (!filho.isLeaf())
      for (int i = filho.numChaves; i >= 0; --i)
         filho.filhos[i + 1] = filho.filhos[i];

   filho.chaves[0]  = atual.chaves[posChave - 1];
   filho.indices[0] = atual.indices[posChave - 1];

   if (!filho.isLeaf())
      filho.filhos[0] = irmao.filhos[irmao.numChaves];

   atual.chaves[posChave - 1]  = irmao.chaves[irmao.numChaves -1];
   atual.indices[posChave - 1] = irmao.indices[irmao.numChaves -1];
   ++filho.numChaves;
   --irmao.numChaves;

   atual.setNode(this->out, pos);
   filho.setNode(this->out, atual.filhos[posChave]);
   irmao.setNode(this->out, atual.filhos[posChave - 1]);   
}

/* brief: funcao que redistribui as chaves de um No com seu pai e irmao
* da direita para a esquerda
* param: posicao do No atual e posicao da chave a ser removida do No
* pre: nenhuma
* pos: empreestimo feito
*/
void ArquivoIndice::emprestaDireita (int pos, int posChave)
{
   BTreeNode atual = BTreeNode::getNode(this->in, pos);
   BTreeNode filho = BTreeNode::getNode(this->in, atual.filhos[posChave]);
   BTreeNode irmao = BTreeNode::getNode(this->in, atual.filhos[posChave + 1]);

   filho.chaves[filho.numChaves] = atual.chaves[posChave];
   filho.indices[filho.numChaves] = atual.indices[posChave];

   if (!irmao.isLeaf())
      filho.filhos[filho.numChaves + 1] = irmao.filhos[0];

   atual.chaves[posChave]  = irmao.chaves[0];
   atual.indices[posChave] = irmao.indices[0];

   for (int i = 1; i < irmao.numChaves; ++i)
   {
      irmao.chaves[i - 1]  = irmao.chaves[i];
      irmao.indices[i - 1] = irmao.indices[i];
   }
   
   if (!irmao.isLeaf())
      for (int i = 1; i <= irmao.numChaves; ++i)
         irmao.filhos[i - 1] = irmao.filhos[i];

   ++filho.numChaves;
   --irmao.numChaves;
   
   atual.setNode(this->out, pos);
   filho.setNode(this->out, atual.filhos[posChave]);
   irmao.setNode(this->out, atual.filhos[posChave + 1]);
}

/* brief: intercala dois irmaos com uma chave do No pai
* da direita para a esquerda
* param: posicao do No atual e posicao da chave a ser removida do No
* pre: nenhuma
* pos: intercalacao efetuada e No irmao removido da arvore
*/
void ArquivoIndice::mergeDireita (int pos, int posChave)
{
   BTreeNode atual = BTreeNode::getNode(this->in, pos);
   BTreeNode filho = BTreeNode::getNode(this->in, atual.filhos[posChave]);
   BTreeNode irmao = BTreeNode::getNode(this->in, atual.filhos[posChave + 1]);

   int posRemove = atual.filhos[posChave + 1];
   int test = atual.filhos[posChave];

   //2 = minimo de chaves
   filho.chaves[1]  = atual.chaves[posChave];
   filho.indices[1] = atual.indices[posChave];

   for (int i = 0; i < irmao.numChaves; ++i)
   {
      filho.chaves[i + 2]  = irmao.chaves[i];
      filho.indices[i + 2] = irmao.indices[i];
   }
   if (!filho.isLeaf())
      for (int i = 0; i <= irmao.numChaves; ++i)
         filho.filhos[i + 2] = irmao.filhos[i];
   
   for (int i = posChave + 1; i < atual.numChaves; ++i)
   {
      atual.chaves[i - 1]  = atual.chaves[i];
      atual.indices[i - 1] = atual.indices[i];
   }
   for (int i = posChave + 2; i <= atual.numChaves; ++i)
      atual.filhos[i - 1] = atual.filhos[i];

   filho.numChaves += irmao.numChaves + 1;
   --atual.numChaves;
   atual.setNode(this->out, pos);
   filho.setNode(this->out, atual.filhos[posChave]);
   removeLista(posRemove);
}

/* brief: intercala dois irmaos com uma chave do No pai
* da esquerda para a direita
* param: posicao do No atual e posicao da chave a ser removida do No
* pre: Apenas pode ser chamada para o caso do No filho mais a direita
* pos: intercalacao efetuada e No irmao removido da arvore
*/
void ArquivoIndice::mergeEsquerda (int pos, int posChave)
{
   BTreeNode atual = BTreeNode::getNode(this->in, pos);
   BTreeNode filho = BTreeNode::getNode(this->in, atual.filhos[posChave - 1]);
   BTreeNode irmao = BTreeNode::getNode(this->in, atual.filhos[posChave]);

   int posRemove = atual.filhos[posChave];

   filho.chaves[filho.numChaves]  = atual.chaves[posChave - 1];
   filho.indices[filho.numChaves] = atual.indices[posChave - 1];
 
   for (int i = 0; i < irmao.numChaves; ++i)
   {
      filho.chaves[i + filho.numChaves + 1]  = irmao.chaves[i];
      filho.indices[i + filho.numChaves + 1] = irmao.indices[i];
   }
   if (!filho.isLeaf())
      for (int i = 0; i <= irmao.numChaves; ++i)
         filho.filhos[i + filho.numChaves + 1] = irmao.filhos[i];

   filho.numChaves += irmao.numChaves + 1;
   --atual.numChaves;
   atual.setNode(this->out, pos);
   filho.setNode(this->out, atual.filhos[posChave - 1]);
   removeLista(posRemove);
}

/* brief: obtem a chave predecessora
* param: posicao da chave, chaveAnt e indiceAnt serao passados como referencia
* pre: nenhuma
* pos: chave e indice predecessor obtidos
*/
void ArquivoIndice::getAnt (int pos, int &chaveAnt, int &indiceAnt) 
{ 
   BTreeNode atual = BTreeNode::getNode(this->in, pos);
   while (!atual.isLeaf())
      atual = BTreeNode::getNode(this->in, atual.filhos[atual.numChaves]);

   chaveAnt  = atual.chaves[atual.numChaves - 1];
   indiceAnt = atual.indices[atual.numChaves - 1]; 
} 

/* brief: Remove um No inteiro do arquivo
* param: posicao do No a ser removido
* pre: posicao valida
* pos: No removido e encadeado na lista de Nos livres
*/
void ArquivoIndice::removeLista (int pos)
{
   BTreeNode atual = BTreeNode:: getNode(this->in, pos);

   //Encadeando o No removido na lista de livres
   atual.setProx(this->cab->getPosLivre());
   atual.setNode(this->out, pos);
   this->cab->setPosLivre(pos);
   this->cab->setCabecalho(this->out);
}

/* brief: obtem a altura da arvore B presente no arquivo
* return: altura da arovre
* pre: nenhuma
* pos: altura retornada
*/
int ArquivoIndice::altura ()
{
   if (this->cab->getPosRaiz() == -1)
      return 0;

   BTreeNode raiz = BTreeNode::getNode(this->in, this->cab->getPosRaiz());   
   return this->alturaAux(raiz.filhos[0]);
}

/* brief: funcao auxiliar que procura a altura recursivamente, da arvore
* param: posicao do No atual
* retorno: 1 e chama recursivamente para o proximo no (caso o atual n for nulo)
* pre: nenhuma
* pos: nenhuma
*/
int ArquivoIndice::alturaAux (int pos)
{
   if (pos == -1) return 1;

   BTreeNode no = BTreeNode::getNode(this->in, pos);   
   return 1 + this->alturaAux(no.filhos[0]);
}

/* brief: imprime na tela as chaves da arvore B de um determinado nivel
* param: nivel atual e posicao do No atual
* pre: nivel ser valido
* pos: chaves exibidas na tela
*/
void ArquivoIndice::mostraNivel (int nivel, int pos)
{
   BTreeNode no = BTreeNode::getNode(this->in, pos);

   if (nivel == 1)
   {
      std::cout << "[";
      for (int i = 0; i < no.numChaves - 1; ++i)
         std::cout << no.chaves[i] << ",";
      std::cout << no.chaves[no.numChaves - 1] << "] ";
   }
   else if (nivel > 1) 
   { 
      for (int i = 0; i <= no.numChaves; ++i)
         mostraNivel(nivel - 1, no.filhos[i]);
   } 
}  

/* brief: imprime a arvore por completo por nivel
* pre: nenhuma
* pos: arvore exibida caso nao seja vazia
*/
void ArquivoIndice::mostrarPorNivel ()
{
   Util::clear();
   std::cout << "[Arvore B por nivel]\n\n";
   
   int h = this->altura();
   if (h == 0) 
   {
      std::cout << "Arvore vazia!\n";
   }
   else
   {
      //printa a raiz;
      BTreeNode no  = BTreeNode::getNode (in, this->cab->getPosRaiz());
      std::cout << "[";
      for (int i = 0; i < no.numChaves - 1; ++i)
         std::cout << no.chaves[i] << ",";
      std::cout << no.chaves[no.numChaves - 1] << "]\n";

      for (int i = 2; i <= h; ++i)
      {
         mostraNivel(i, this->cab->getPosRaiz());
         std::cout << "\n";
      }
   }
   Util::pressRetornar();
}

/* brief: Obtem todos os indices em ordem crescente da posicao dos dados
* return: vetor de inteiro com os indices ordenados
* pre: nenhuma
* pos: indices obtidos
*/
std::vector<int> ArquivoIndice::getIndices ()
{
   std::vector<int> indices;

   if (this->cab->getPosRaiz() != -1)
      getIndicesAux(this->cab->getPosRaiz(), indices);
   
   return indices;
}

/* brief: funcao auxiliar para obter os indices em ordem crescente da arvore
* param: posicao do No atual do no e vetor de indices por referencia
* pre: nenhuma
* pos: indice armazenado caso exista no No
*/
void ArquivoIndice::getIndicesAux (int pos, std::vector<int> &indices)
{
   BTreeNode no = BTreeNode::getNode(this->in, pos);
   
   int i;
   for (i = 0; i < no.numChaves; ++i)
   {
      if (no.isLeaf() == false)
         this->getIndicesAux(no.filhos[i], indices);
      indices.push_back(no.indices[i]);
   }
   if (no.isLeaf() == false)
      this->getIndicesAux(no.filhos[i], indices);
}

/* brief: obtem um indice do arquivo de dados a partir de uma chave da arvore
* param: chave
* return: indice do arquivo de dados que relaciona com a chave
* pre: nenhuma
* pos: indice obtido
*/
int ArquivoIndice::getIndice (int chave)
{
   if (this->cab->getPosRaiz() == -1)
      return -1;

   return getIndiceAux (chave, this->cab->getPosRaiz());
}

/* brief: funcao auxiliar que procura pelo indice relacionado a uma chave
* param: chave e posicao atual
* return: indice obtido caso a chave esteja no No atual
* pre: nenhuma
* pos: nenhuma
*/
int ArquivoIndice::getIndiceAux (int chave, int pos)
{
   if (pos == -1) return -1;

   BTreeNode no = BTreeNode::getNode(this->in, pos);
   int i = 0;
   while (i < no.numChaves && chave > no.chaves[i])
      ++i;     
   //encontrou
   if (i < no.numChaves && chave == no.chaves[i])
      return no.indices[i];

   return getIndiceAux(chave, no.filhos[i]);
}

/* brief: destrutor da classe, responsavel por desalocar da memoria o cabecalho 
* pre: cabecalho alocado
* pos: cabecalho desalocado
*/
ArquivoIndice::~ArquivoIndice ()
{
   delete this->cab;
}