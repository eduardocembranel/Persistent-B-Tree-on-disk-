#include "App.hpp"

/* brief: funcao principal que inicializa o programa
* pre: nenhuma
* pos: retorna flag para SO - 0: sucesso 1: erro
*/
int main ()
{
   App *app = new App();
   app->run();
   delete app;
   return 0;
}