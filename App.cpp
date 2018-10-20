#include <iostream>

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
            break;
         case INSERE_MEDICO:
            this->insereDado();
            break;
         case ALTERA_MEDICO:
            break;
         case BUSCA_MEDICO:
            this->buscaMedico();
            break;
         case REMOVE_MEDICO:
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
   std::cout << "[Cadastros]\n\n";
   if (indices.size() == 0)
      std::cout << "Nenhum medico cadastrado!\n";
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
      NoMedico dado = this->arq->getData (indice);
      std::cout << dado.medico;
   }
   Util::pressRetornar();
}

void App::mostraMenu ()
{
   Util::clear();
   std::cout << "Cadastramento de Medicos\n\n"
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

App::~App ()
{
   delete arq;
   delete arq2;
}