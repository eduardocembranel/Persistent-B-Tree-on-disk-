#ifndef BTREENODE_HPP
#define BTREENODE_HPP

#define ORDEM 5

#include <fstream>

class BTreeNode
{
   public: //mudar para privado dps
      int numChaves;
      int chaves[ORDEM];
      int filhos[ORDEM + 1];
      int indices[ORDEM];
      int prox;

   public:
      BTreeNode (int, int, int);
      BTreeNode ();
      void setProx (int);
      int getProx ();
      bool overflow ();
      bool isLeaf ();
      void setNode (std::ofstream &, int);
      static BTreeNode* getNode (std::ifstream &, int);

};

#endif // !BTREENODE_HPP