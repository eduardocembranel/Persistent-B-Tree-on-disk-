#ifndef MEDICO_HPP
#define MEDICO_HPP

#include <string>
#include <iostream>

class Medico
{
   public: //mudar para privado dps
      int id;
      int crm;
      char nome[100];
      char sexo[100];
      char cpf[100];
      char especialidade[100];
      char rg[100];
      char telefone[100];
      char celular[100];
      char email[100];
      char endereco[100];
      char nascimento[100];      

   public:
      void setMedico ();
      friend std::ostream& operator<< (std::ostream&, const Medico&);

};

#endif // !MEDICO_HPP