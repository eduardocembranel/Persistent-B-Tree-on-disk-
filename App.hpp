#ifndef APP_HPP
#define APP_HPP

#include "ArquivoDados.hpp"
#include "ArquivoIndice.hpp"
#include "Medico.hpp"

class App
{
   public:
      App ();
      void run ();
      ~App ();

   private:
      ArquivoDados  *arq;
      ArquivoIndice *arq2;
      void imprimirCadastro ();
      void insereDado ();
      void buscaMedico ();
      void mostraMenu ();

      enum MenuEstado
      {
         CARREGA_ARQUIVO = 1,
         INSERE_MEDICO,
         ALTERA_MEDICO,
         BUSCA_MEDICO,
         REMOVE_MEDICO,
         IMPRIME_CADASTRO,
         IMPRIME_ARVORE,
         SAIR
      };
};

#endif // !APP_HPP