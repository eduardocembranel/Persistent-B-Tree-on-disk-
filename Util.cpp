#include <iostream>
#include <sstream>
#include <limits>
#include <cstring>
#include <cstdlib>
#include <cctype>

#include "Util.hpp"

/* brief: construtor privado, impossibilitando a instancia de objetos
* pre: nenhuma
* pos: nenhuma
*/
Util::Util () {}

/* brief: Faz o split do vetor de strings
* param: uma string com as informações do médico e um caracter divisor de dados (:)
* pre: Nenhuma
* pos: dividir a string em pedaços menores
*/
std::vector<std::string> Util::splitString (std::string s, char c)
{
   int tam = s.length();
   std::vector<std::string> separado;

   for (int j = 0, k = 0; j < tam; ++j) 
   {
      if (s[j] == c) 
      {
         std::string ch = s.substr(k, j - k);
         k = j + 1;
         separado.push_back(ch);
      }
      if (j == tam - 1) 
      {
         std::string ch = s.substr(k, j - k + 1);
         separado.push_back(ch);
      }
   }
   return separado;
}

/* brief: limpa a tela do console
* pre: nenhuma
* pos: tela limpada do console
*/
void Util::clear ()
{
   system("cls");
}

/* brief: exibe a mensagem esperando por um ENTER e aguarda o mesmo
* pre: buffer de entrada esta limpo
* pos: nenhuma
*/
void Util::pressRetornar ()
{
   std::cout << "\nPressione ENTER para retornar...";
   Util::flushInput();
}

/* brief: limpa os dados de entrada, para tirar espaços desnescessários
* pre: nenhuma
* pos:ter retirado os espaços desnecessários
*/
void Util::flushInput ()
{
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/* brief: transforma os caracteres em inteiros
* pre: a string ser válida
* pos: passar os caracteres transformados em números
*/
int Util::strToInt (const std::string &str)
{
   int elem;
   std::istringstream (str) >> elem;
   return elem;
}

/* brief: verifica se a string é nula
* pre: nenhuma
* pos: retorna se o comprimento da string é maior que 0
*/
bool Util::ehNula (const std::string &str)
{
   return str.size() == 0;
}

/* brief: faz a verificação se a passagem da data esta no formato certo
* pre: uma string pre carregada
* pos: retorna se a string é válida
*/
bool Util::ehFormatoData (const std::string &str)
{
   if (str.size() != 10) 
      return false;

   if (str[2] != '/' || str[5] != '/')
      return false;
   
   if (!isdigit(str[0]) || !isdigit(str[1]) || !isdigit(str[3]) ||
      !isdigit(str[4]) || !isdigit(str[6]) || !isdigit(str[7]) ||
      !isdigit(str[8]) || !isdigit(str[9]))
      return false;

   return true;
}

/* brief: verifica se a string possui apenas digitos ou tracos
* pre: nenhum
* pos: retorna verdadeiro ou falso
*/
bool Util::ehNumTraco (const std::string &str)
{
   for (char it : str)
      if (it != '-' && !isdigit(it))
         return false;
   return true;
}

/* brief: verifica se a string passada é um inteiro 
* pre: nenhum
* pos: nenhum
*/
bool Util::ehInt (const std::string &str)
{
   char *fim;
   strtol(str.c_str(), &fim, 10);

   return (*fim == 0);
}     