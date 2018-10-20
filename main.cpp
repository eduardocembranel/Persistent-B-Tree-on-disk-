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
   App *app = new App();
   app->run();
   delete app;
   return 0;
}