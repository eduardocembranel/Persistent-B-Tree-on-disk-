#include "Arquivo.hpp"

Arquivo::Arquivo (const std::string &fileName)
{
   this->fileName = fileName;
   this->out.open(fileName, std::ios::out | std::ios::binary);
   this->in.open(fileName, std::ios::in | std::ios::binary);
}