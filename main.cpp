#include <iostream>
#include <cstdio>
#include <cstring>
#include "CabecalhoDados.hpp"
#include "ArquivoDados.hpp"
using namespace std;
int main ()
{
   Arquivo *arq = new ArquivoDados("teste.bin");
   
   Medico t1;
   Medico t2;
   Medico t3;
   Medico t4;
   
   t1.id = 1;
   t1.crm = 99;
   t2.id = 2;
   strcpy(t2.nome,"wef");
   t2.crm = 98;
   t3.id = 50;
   t4.id = 40;

   arq->insere(t1);
   arq->insere(t2);
   arq->insere(t3);
   arq->insere(t4);

   FILE *teste = fopen("teste.bin", "rb");
   CabecalhoDados *cab = new CabecalhoDados();
   fseek(teste, 0, SEEK_SET);
   fread(cab, sizeof(CabecalhoDados), 1, teste);
   fclose(teste);

   cout << "CABECALHO: \n";
   cout << cab->getPosCabeca() << "\n";
   cout << cab->getPosTopo() << "\n";
   cout << cab->getPosLivre() << "\n";

   NoMedico *med1 = arq->getData(0);
   NoMedico *med2 = arq->getData(1);
   NoMedico *med3 = arq->getData(2);
   NoMedico *med4 = arq->getData(3);

   cout << "Id-Medico 1:[" << med1->medico.crm << "]\n";
   cout << "Id-Medico 2:[" << med2->medico.nome << "]\n";
   cout << "Id-Medico 3:[" << med3->medico.id << "]\n";
   cout << "Id-Medico 4:[" << med4->medico.id << "]\n";

 //  delete med1;
 //  delete med2;
 //  delete arq;
   return 0;
}