#include "App.hpp"

App::App ()
{
   arq = new ArquivoDados("dados.bin");
   arq2 = new ArquivoIndice("indices.bin");
}

void App::run ()
{
   arq2->insere(2, 0);
   arq2->insere(1, 0);
   arq2->insere(6, 0);
   arq2->insere(8, 0);
   arq2->insere(4, 0);
   arq2->insere(5, 0);
   arq2->insere(10, 0);
   arq2->insere(20, 0);
   arq2->insere(30, 0);
   arq2->insere(3, 0);
   arq2->insere(70, 0);
   arq2->insere(90, 0);
   arq2->insere(43, 0);
   arq2->insere(7, 0);
   arq2->insere(11, 0);
   arq2->insere(12, 0);
   arq2->insere(15, 0);
   arq2->insere(18, 0);
   arq2->insere(19, 0);
   arq2->insere(14, 0);
   
   arq2->mostrarPorNivel();

}