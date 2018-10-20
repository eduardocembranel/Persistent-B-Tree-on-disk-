#include "Medico.hpp"

std::ostream& operator<< (std::ostream &out, const Medico &medico)
{
   out << "\n"
       << "Medico:        " << medico.nome          << "\n"
       << "Id:            " << medico.id            << "\n"
       << "Nascimento:    " << medico.nascimento    << "\n"
       << "Sexo:          " << medico.sexo          << "\n"
       << "CPF:           " << medico.cpf           << "\n"
       << "CRM:           " << medico.crm           << "\n"
       << "RG:            " << medico.rg            << "\n"
       << "Especialidade: " << medico.especialidade << "\n"
       << "Telefone:      " << medico.telefone      << "\n"
       << "Celular:       " << medico.celular       << "\n"
       << "E-mail:        " << medico.email         << "\n"
       << "Endereco:      " << medico.endereco      << "\n";   
   return out;
}

void Medico::setMedico ()
{
   std::cout << "Nome: ";
   std::cin  >> this->nome;
   std::cout << "Id: ";
   std::cin  >> this->id;
   std::cout << "Nacimento: ";
   std::cin  >> this->nascimento;
   std::cout << "Sexo: ";
   std::cin  >> this->sexo;
   std::cout << "CPF: ";
   std::cin  >> this->cpf;
   std::cout << "CRM: ";
   std::cin  >> this->crm;
   std::cout << "RG: ";
   std::cin  >> this->rg;
   std::cout << "Especialidade: ";
   std::cin  >> this->especialidade;
   std::cout << "Telefone: ";
   std::cin  >> this->telefone;
   std::cout << "Celular: ";
   std::cin  >> this->celular;
   std::cout << "E-mail: ";
   std::cin  >> this->email;
   std::cout << "Endereco: ";
   std::cin  >> this->endereco; 
}