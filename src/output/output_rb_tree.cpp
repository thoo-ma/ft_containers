#include "rb_tree.hpp"
#include "ft_pair.hpp"
#include <cassert>

int main()
{
    {
        ft::rb_tree<int> tree;
        for (int i = 0; i < 18; i++) {
            tree.insert(tree.root_node(), i);
            tree.print(tree.root_node());
            std::cout << std::endl;
        }
    }
    {
        ft::rb_tree<int> tree;
        for (int i = 19; i > 0; i--) {
            tree.insert(tree.root_node(), i);
            tree.print(tree.root_node());
            std::cout << std::endl;
        }
    }
    {
        ft::rb_tree<int> tree;
        tree.insert(tree.root_node(), 2);
        tree.print(tree.root_node()); std::cout << std::endl;
        tree.insert(tree.root_node(), 1);
        tree.print(tree.root_node()); std::cout << std::endl;
        tree.insert(tree.root_node(), 5);
        tree.print(tree.root_node()); std::cout << std::endl;
        tree.insert(tree.root_node(), 8);
        tree.print(tree.root_node()); std::cout << std::endl;
        tree.insert(tree.root_node(), 7);
        tree.print(tree.root_node()); std::cout << std::endl;
        tree.insert(tree.root_node(), 3);
        tree.print(tree.root_node()); std::cout << std::endl;
        tree.insert(tree.root_node(), 4);
        tree.print(tree.root_node()); std::cout << std::endl;
    }
    /*
    {
        ft::rb_tree<int>::node_type a;
        ft::rb_tree<int>::node_type b;

        assert(a.key == 0);
        assert(b.key == 0);

        a.key = 42;
        b = a;

        assert(a.key == 42);
        assert(b.key == 42);

        ft::rb_tree<int>::node_type c(42);

        assert(c.key == a.key);
    }
    {
        ft::rb_tree<int> a;

        for (int i = 0; i < 21; i++)
            a.insert(a.root_ref(), NULL, i);

        ft::rb_tree<int> b(a);

        std::cout << "a: "; a.print(a.root_node()); std::cout << std::endl;
        std::cout << "b: "; b.print(a.root_node()); std::cout << std::endl;
    }
    {
        ft::pair<const int,char> p;
        ft::rb_tree<ft::pair<const int,char>> a;
        ft::rb_tree<ft::pair<const int,char>> b(a);
    }
    */
    return 0;
}
