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
      int ant;

   public:
      BTreeNode (int, int);
      BTreeNode ();
      void setProx (int);
      void setAnt (int);
      int getProx ();
      int getAnt ();
      bool overflow ();
      bool isLeaf ();
      void setNode (std::ofstream &, int);
      static BTreeNode* getNode (std::ifstream &, int);
      static BTreeNode* split (BTreeNode*&, int*, int*);

};

#endif // !BTREENODE_HPP