#ifndef MEDICO_HPP
#define MEDICO_HPP

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

      void setMedico ();
      friend std::ostream& operator<< (std::ostream&, const Medico&);

};

#endif // !MEDICO_HPP