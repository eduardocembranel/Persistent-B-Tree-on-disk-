#include <iostream>
#include <cstdio>
#include <cstring>
#include "CabecalhoDados.hpp"
#include "ArquivoDados.hpp"
#include "ArquivoIndice.hpp"
#include "Util.hpp"
#include <vector>
#include "App.hpp"
using namespace std;
int main ()
{
  // ArquivoDados  *arq  = new ArquivoDados("dados.bin");
  // ArquivoIndice *arq2 = new ArquivoIndice("indice.bin");

   //int pos;
  // pos = arq->insere(m1);
  // arq2->insere(m1.id, pos);
  // pos = arq->insere(m2);
  // arq2->insere(m2.id, pos);
  // pos = arq->insere(m3);
  // arq2->insere(m3.id, pos);
  // pos = arq->insere(m4);
   

  // vector<string> s =  Util::splitString("romulo:alguem:123:04:123", ':');
   
  // for (int i = 0; i < s.size(); ++i)
  //    cout << s[i] << "\n";

   App *app = new App();

   app->run();

   return 0;
}