#ifndef BTREENODE_HPP
#define BTREENODE_HPP

#define ORDEM 5

class BTreeNode
{
   private:
      int numChaves;
      int chaves[ORDEM];
      int posFilhos[ORDEM + 1];
      int indices[ORDEM];

   public:
      BTreeNode ();
};

#endif // !BTREENODE_HPP