#ifndef APP_HPP
#define APP_HPP

/*
* \file App.hpp
* \class App
* \brief Classe responsavel por gerenciar as funcionalidades do programa
* \author Carlos Pedroso
* \author Eduardo Cembranel
*/

#include <string>

#include "ArquivoDados.hpp"
#include "ArquivoIndice.hpp"
#include "Medico.hpp"

class App
{
   public:
      /* brief: construtor padrao: inicializa os arquivos de dados e indice
      * pre: nenhuma
      * pos: arquivos inicializados 
      */
      App ();
      
      /* brief: faz a escolha da opção do usuário sobre qual função utilizar
      * pre: arquivos deve estar carregados
      * pos: levar o usuário a uma função escolhida 
      */
      void run ();

      /* brief: esse é o destrutor da classe
      * pre: nenhuma
      * pos: liberar a memória alocada pelos arquivos
      */
      ~App ();

   private:
      ArquivoDados  *arq; //arquivo de dados (medicos)
      ArquivoIndice *arq2; //arquivo de indices (arvore B)
      
      /* brief: percorre chave por chave da arvore b, 
      * retornando os indices do arquivo de dados correspondente aos dados, 
      * obtem os dados e imprime-os
      * pre: nenhum
      * pos: ter imprimido os dados dos médicos, caso existentam 
      */
      void imprimirCadastro ();

      /* brief: insere o medico no arquivo de dados e a chave no arquivo de indice
      * pre: nenhum
      * pos: ter inserido o médico na arvore e no arquivo
      */
      void insereDado ();

      /* brief: Faz a busca pelo médico desejado a partir do seu ID
      * pre: nenhuma
      * pos: mostrar na tela os dados do médico, caso exista
      */
      void buscaMedico ();

      /* brief: Faz a alteração dos dados já cafastrados do médico
      * pre: médico desejado ja ter sido inserido no arquivo
      * pos: ter alterado os dados do médico desejado
      */
      void alteraMedico ();

      /* brief: Faz a remoção do médico a partir de um id buscado
      * pre: o usuário ter passado um id válido para busca
      * pos: os dados do médico terem sido removido 
      */
      void removeMedico ();

      /* brief: mostra na tela o menu de opções para o usuário
      * pre: nenhuma
      * pos: ter printado na tela as informações necessárias
      */
      void mostraMenu ();

      /* brief: Carrega o arquivo de dados para a memória
      * pre: o Arquivo existir e ser válido
      * pos: ter carregado parte do arquivo para a memória
      */
      void carregaArquivo ();

      /* brief: Verifica se os valores passados são validos
      * pre: passagem dos dados lidos do arquivo
      * pos: retornar se os valores são verdadeiros ou não
      */
      bool ehValida (std::vector<std::string>);
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