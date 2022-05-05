#include "rb_tree.hpp"

void rb_tree_print_test()
{
    ft::rb_tree<int> tree;

    tree.insert(42);

    tree.print();

    //ft::rb_tree<std::pair<int,double>> t;

   // for (int i = 0; i < 10; i++)
   //     tree.insert(i);

}

int main()
{
    rb_tree_print_test();
    return 0;
}
