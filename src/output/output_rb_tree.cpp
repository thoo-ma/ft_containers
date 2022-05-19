#include "rb_tree.hpp"

int main()
{
    {
        ft::rb_tree<int> tree;
        for (int i = 0; i < 6; i++) {
            tree.insert(tree.root_ref(), NULL, i);
            tree.print(tree.root_node()); std::cout << std::endl;
        }
    }
    {
        ft::rb_tree<int> tree;
        for (int i = 6; i > 0; i--) {
            tree.insert(tree.root_ref(), NULL, i);
            tree.print(tree.root_node()); std::cout << std::endl;
        }
    }
    return 0;
}
