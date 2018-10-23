#ifndef MEDICO_HPP
#define MEDICO_HPP

/*
* \file Medico.hpp
* \class Medico
* \brief Classe que representa a entidade "Medico"
* \author Carlos Pedroso
* \author Eduardo Cembranel
*/

#include <iostream>

#define STR_SIZE 100

class Medico
{
   public:
      int id;
      int crm;
      char nome[STR_SIZE];
      char sexo[STR_SIZE];
      char cpf[STR_SIZE];
      char especialidade[STR_SIZE];
      char rg[STR_SIZE];
      char telefone[STR_SIZE];
      char celular[STR_SIZE];
      char email[STR_SIZE];
      char endereco[STR_SIZE];
      char nascimento[STR_SIZE];

      /* brief: Seter da classe
      * pre: nenhuma
      * pos: nenhuma
      */
      void setMedico ();

      /* brief: mostra na tela os dados do médico
      * param: ponteiro para a saida de dados, ponteiro para o identificador do médico
      * pre: as informações do médico terem sido carregadas
      * pos: nenhuma
      */
      friend std::ostream& operator<< (std::ostream&, const Medico&);

};

#endif // !MEDICO_HPP