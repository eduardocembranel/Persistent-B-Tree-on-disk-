#include "Arquivo.hpp"

/* brief: construtor padrao: abre os arquivos de leitura e escrita
* pre: nenhuma
* pos: arquivos de leitura e escrita abertos
*/
Arquivo::Arquivo (const std::string &fileName)
{
   this->fileName = fileName;
   this->out.open(fileName, std::ios::out | std::ios::binary);
   this->in.open(fileName, std::ios::in | std::ios::binary);
}

/* brief: destrutor: fecha os arquivos de leitura e escrita 
* pre: arquivos deve estar abertos
* pos: arquivos de leitura e escrita fechados 
*/
Arquivo::~Arquivo ()
{
   this->out.close();
   this->in.close();
}