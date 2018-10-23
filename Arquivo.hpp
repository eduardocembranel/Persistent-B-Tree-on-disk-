#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

/*
* \file Arquivo.hpp
* \class Arquivo
* \brief Superclasse que representa um gerenciador de arquivo
* \author Carlos Pedroso
* \author Eduardo Cembranel
*/

#include <string>
#include <fstream>

#include "NoMedico.hpp"

class Arquivo
{
   protected:
      std::string fileName; //nome do arquivo
      std::ifstream in; //buffer para leitura
      std::ofstream out; //buffer para escrita

      /* brief: construtor padrao: abre os arquivos de leitura e escrita
      * pre: nenhuma
      * pos: arquivos de leitura e escrita abertos
      */
      Arquivo (const std::string&);

      /* brief: destrutor: fecha os arquivos de leitura e escrita 
      * pre: arquivos deve estar abertos
      * pos: arquivos de leitura e escrita fechados 
      */
      ~Arquivo ();   
};

#endif // !ARQUIVO_HPP