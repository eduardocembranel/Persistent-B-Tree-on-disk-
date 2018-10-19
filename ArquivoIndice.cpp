#include "ArquivoIndice.hpp"

ArquivoIndice::ArquivoIndice (const std::string &fileName) : Arquivo(fileName)
{  
   this->cab = new CabecalhoIndice();
   this->cab->setCabecalho(this->out); //coloca o cabecalho no arquivo
}