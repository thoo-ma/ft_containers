#include "rb_tree.hpp"

void rb_tree_print_test()
{
    ft::rb_tree<int> tree;

  //  ft::rb_node<int> ** root = tree.root();

  //  std::cout << "root addr: " << root << std::endl;
  //  std::cout << "root node addr: " << *root << std::endl;

    tree.insert(tree.root(), tree.root()->parent, 21);

  //  std::cout << "root addr: " << root << std::endl;
  //  std::cout << "root node addr: " << *root << std::endl;

    tree.insert(tree.root(), tree.root()->parent, 42);

  //  std::cout << "root addr: " << root << std::endl;
  //  std::cout << "root node addr: " << *root << std::endl;
  //  std::cout << "root node left addr: " << (*root)->left << std::endl;
  //  std::cout << "root node right addr: " << (*root)->right << std::endl;

   // tree.print();

    //ft::rb_tree<std::pair<int,double>> t;

   // for (int i = 0; i < 10; i++)
   //     tree.insert(i);

}

int main()
{
    rb_tree_print_test();
    return 0;
}
