#ifndef BTREENODE_HPP
#define BTREENODE_HPP

#include <fstream>

class BTreeNode
{
   friend class ArquivoIndice;
   
   private:
      static const int ORDEM  = 5;
      static const int MINIMO = 2;
      int numChaves = 4;
      int chaves[ORDEM];
      int filhos[ORDEM + 1];
      int indices[ORDEM];
      int prox;
      int ant;

      BTreeNode (int, int);
      BTreeNode ();
      void setProx (int);
      void setAnt (int);
      int getProx ();
      int getAnt ();
      bool overflow ();
      bool underflow ();
      bool isLeaf ();
      void setNode (std::ofstream &, int);
      static BTreeNode getNode (std::ifstream &, int);
      static BTreeNode split (BTreeNode &, int *, int *);

};

#endif // !BTREENODE_HPP