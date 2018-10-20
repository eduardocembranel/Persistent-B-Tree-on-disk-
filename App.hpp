#ifndef APP_HPP
#define APP_HPP

#include "ArquivoDados.hpp"
#include "ArquivoIndice.hpp"

class App
{
   public:
      App ();
      void run ();

   private:
      ArquivoDados  *arq;
      ArquivoIndice *arq2;
      
};

#endif // !APP_HPP