#include <iostream>
#include <cstdio>
#include <cstring>
#include "CabecalhoDados.hpp"
#include "ArquivoDados.hpp"
#include "ArquivoIndice.hpp"
using namespace std;
int main ()
{
   ArquivoDados  *arq  = new ArquivoDados("dados.bin");
   ArquivoIndice *arq2 = new ArquivoIndice("indice.bin");

   Medico m1;
   Medico m2;
   Medico m3;

   m1.id = 1000;
   m2.id = 2000;
   m3.id = 3000;

   int pos;
   pos = arq->insere(m1);
   arq2->insere(m1.id, pos);
   pos = arq->insere(m2);
   arq2->insere(m2.id, pos);
   pos = arq->insere(m3);
   arq2->insere(m3.id, pos);

   NoMedico  *med1 = arq->getData(0);
   NoMedico  *med2 = arq->getData(1);
   NoMedico  *med3 = arq->getData(2);
   BTreeNode *no1  = BTreeNode::getNode (arq2->in, 0);

   cout << med1->medico.id << "\n";
   cout << no1->chaves[0] << "\n";
   cout << med2->medico.id << "\n";
   cout << no1->chaves[1] << "\n";
   cout << med3->medico.id << "\n";
   cout << no1->chaves[2] << "\n";


   return 0;
}