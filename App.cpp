#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#include "App.hpp"
#include "Util.hpp"

App::App ()
{
   arq  = new ArquivoDados("dados.bin");
   arq2 = new ArquivoIndice("indices.bin");
}

void App::run ()
{
   int escolha;
   do
   {
      this->mostraMenu();
      std::cin >> escolha;
      Util::flushInput();
      switch (escolha)
      {
         case CARREGA_ARQUIVO:
            this->carregaArquivo();
            break;
         case INSERE_MEDICO:
            this->insereDado();
            break;
         case ALTERA_MEDICO:
            this->alteraMedico();
            break;
         case BUSCA_MEDICO:
            this->buscaMedico();
            break;
         case REMOVE_MEDICO:
            this->removeMedico();
            break;
         case IMPRIME_CADASTRO:
            this->imprimirCadastro();
            break;
         case IMPRIME_ARVORE:
            this->arq2->mostrarPorNivel();
            break;
         case SAIR:
            break;
         default:
            std::cout << "\nOpcao invalida!\n";
            Util::pressRetornar();  
            break;
      }
   } while (escolha != SAIR);
}

//insere o medico no arquivo de dados e a chave no arquivo de indice
void App::insereDado ()
{
   Util::clear();
   std::cout << "[Inserir Medico]\n\n";

   Medico elem;
   elem.setMedico();
   int pos = arq->insere(elem);
   arq2->insere(elem.id, pos);

   std::cout << "\n";
   Util::pressRetornar();
}

//percorre chave por chave da arvore b, retornando o indice do arquivo de dados
//correspondente ao dado, obtem o dado e imprime-o
void App::imprimirCadastro ()
{
   std::vector<int> indices = this->arq2->getIndices();

   Util::clear();
   std::cout << "[Cadastros]\n";
   if (indices.size() == 0)
      std::cout << "\nNenhum medico cadastrado!\n";
   else
      for (int i = 0; i < indices.size(); ++i)
      {
         NoMedico temp = this->arq->getData(indices[i]);
         std::cout << temp.medico << "\n";
      }
   Util::pressRetornar();
}

void App::buscaMedico ()
{
   Util::clear();
   std::cout << "[Buscar dados de Medico]\n\nInsira o id: ";
   int id;
   std::cin  >> id;
   Util::flushInput();
   
   int indice = this->arq2->getIndice(id);
   if (indice == -1)
   {
      std::cout << "\nMedico nao encontrado (Id invalido)!\n";
   }
   else
   {
      NoMedico dado = this->arq->getData(indice);
      std::cout << dado.medico;
   }
   Util::pressRetornar();
}

void App::removeMedico ()
{
   Util::clear();
   std::cout << "[Remover medico]\n\nInsira o id: ";
   int id;
   std::cin  >> id;
   Util::flushInput();
   int indice = this->arq2->remove(id);
   if (indice == -1)
   {
      std::cout << "\nMedico nao encontrado (Id invalido)!\n";
   }
   else
      this->arq->remove(indice);

   Util::pressRetornar();
}

void App::mostraMenu ()
{
   Util::clear();
   std::cout << "[Cadastramento de Medicos]\n\n"
             << "[1] Carregar arquivo de incializacao\n"
             << "[2] Inserir medico\n"
             << "[3] Alterar medico\n"
             << "[4] Buscar dados de medico\n"
             << "[5] Remover medico\n"
             << "[6] Imprimir cadastro\n"
             << "[7] Imprimir arvore B\n"
             << "[8] Sair\n\n"
             << ">> ";
}

void App::alteraMedico ()
{
   Util::clear();
   std::cout << "[Alterar medico]\n\nInsira o id: ";
   int id;
   std::cin  >> id;
   Util::flushInput();
   int indice = this->arq2->getIndice(id);
   if (indice == -1)
   {
      std::cout << "\nMedico nao encontrado (Id invalido)!\n";
   }
   else
   {
      NoMedico dado = this->arq->getData (indice);
      std::cout << dado.medico << "\n"
                << "Selecione a informacao a ser alterada:\n"
                << "[1] Telefone\n"
                << "[2] Celular\n"
                << "[3] E-mail\n"
                << "[4] Endereco\n"
                << "[5] Voltar\n\n"
                << ">> ";
      enum opcoes { TELEFONE = 1, CELULAR, EMAIL, ENDERECO, VOLTAR };
      int escolha;
      std::cin >> escolha;
      Util::flushInput();
      if (escolha >= TELEFONE && escolha <= ENDERECO)
      {
         switch (escolha)
         {
            case TELEFONE:
               std::cout << "\nNovo telefone: ";
               std::cin  >> dado.medico.telefone; /////////mudar usando setters da classe medico
               break;
            case CELULAR:
               std::cout << "\nNovo celular: ";
               std::cin  >> dado.medico.celular;
               break;
            case EMAIL:
               std::cout << "\nNovo telefone: ";
               std::cin  >> dado.medico.email;
               break;
            case ENDERECO:
               std::cout << "\nNovo telefone: ";
               std::cin  >> dado.medico.telefone;
               break;
         }
         this->arq->insereNo(&dado, indice); 
      }
      else if (escolha != VOLTAR)
      {
         std::cout << "\nOpcao invalida!\n";
      }
   }
   Util::pressRetornar();
}

void App::carregaArquivo ()
{
   Util::clear();
   std::cout << "[Carregar arquivo de inicializacao]\n\nInsira o nome do arquivo: ";
   std::string fileName;
   std::cin >> fileName;
   Util::flushInput();

   std::ifstream fBuffer(fileName, std::ios::in);
   if (fBuffer.fail())
   {
      std::cout << "\nArquivo nao encontrado!\n";
   }
   else
   {
      std::string linha;
      while (std::getline(fBuffer, linha))
      {
         std::vector<std::string> info = Util::splitString(linha, ':');
         if (this->ehValida(info))
         {
            Medico elem;
            elem.id                  = Util::strToInt(info[0]);
            elem.crm                 = Util::strToInt(info[4]);
            strcpy(elem.nome,          info[1].c_str());
            strcpy(elem.sexo,          info[2].c_str());
            strcpy(elem.cpf,           info[3].c_str());
            strcpy(elem.especialidade, info[5].c_str());
            strcpy(elem.rg,            info[6].c_str());
            strcpy(elem.telefone,      info[7].c_str());
            strcpy(elem.celular,       info[8].c_str());
            strcpy(elem.email,         info[9].c_str());
            strcpy(elem.endereco,      info[10].c_str());
            strcpy(elem.nascimento,    info[11].c_str());
            
            int pos = arq->insere(elem);
            arq2->insere(elem.id, pos);
         }
      }      
   }
   fBuffer.close();
   Util::pressRetornar();
}

bool App::ehValida (std::vector<std::string> vet)
{
   if (vet.size() != 12)
      return false;

   if (!Util::ehInt(vet[0]) || !Util::ehInt(vet[4]))
      return false;

   if (Util::ehNula(vet[1]) || Util::ehNula(vet[2]) ||
       Util::ehNula(vet[3]) || Util::ehNula(vet[6]))
      return false;

   return true;
}

App::~App ()
{
   delete arq;
   delete arq2;
}