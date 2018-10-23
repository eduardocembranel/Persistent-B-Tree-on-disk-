#include "Medico.hpp"
#include "Util.hpp"

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
   std::cin.getline(this->nome, sizeof(this->nascimento));
   std::cout << "Id: ";
   std::cin  >> this->id;
   Util::flushInput();
   std::cout << "Nacimento: ";
   std::cin.getline(this->nascimento, sizeof(this->nascimento));
   std::cout << "Sexo: ";
   std::cin.getline(this->sexo, sizeof(this->sexo));
   std::cout << "CPF: ";
   std::cin.getline(this->cpf, sizeof(this->cpf));
   std::cout << "CRM: ";
   std::cin  >> this->crm;
   Util::flushInput();
   std::cout << "RG: ";
   std::cin.getline(this->rg, sizeof(this->rg));
   std::cout << "Especialidade: ";
   std::cin.getline(this->especialidade, sizeof(this->especialidade));
   std::cout << "Telefone: ";
   std::cin.getline(this->telefone, sizeof(this->telefone));
   std::cout << "Celular: ";
   std::cin.getline(this->celular, sizeof(this->celular));
   std::cout << "E-mail: ";
   std::cin.getline(this->email, sizeof(this->email));
   std::cout << "Endereco: ";
   std::cin.getline(this->endereco, sizeof(this->endereco));
}