#include <map>
#include <cassert>
#include "rbtree.hpp"
//#include "rbtree_no_sentinel.hpp"

int main()
{
    ft::rbtree<int> tree;

    std::cout << "-- before --" << std::endl;
    std::cout << tree.sentinel()->left->key << std::endl;
    std::cout << tree.sentinel()->right->key << std::endl;
    std::cout << tree.sentinel()->parent->key << std::endl;

    tree.insert(10);

    tree.make_graph();

    assert(*tree.end() == *tree.sentinel());

    std::cout << "-- after --" << std::endl;
    std::cout << tree.sentinel()->left->key << std::endl;
    std::cout << tree.sentinel()->right->key << std::endl;
    std::cout << tree.sentinel()->parent->key << std::endl;

    //assert(*(--tree.end()) == *tree.root());

//    ft::rbtree<int>::iterator it = tree.end();
//
//    std::cout << (*(--it)).key << std::endl;
//
//    std::cout << "min: " << (*(tree.min(tree.root()))).key << std::endl;
//    std::cout << "max: " << (*(tree.max(tree.root()))).key << std::endl;


    /*

    {
        ft::rbtree<int> tree;

        tree.insert(50);
        tree.insert(79);
        tree.insert(21);
        tree.insert(88);
        tree.insert(16);
        tree.insert(67);
        tree.insert(10);
        tree.insert(19);
        tree.insert(11);
        tree.insert(42);
        tree.insert(27);
        tree.insert(90);
        tree.insert(55);

        // insert case 1: uncle is red
        tree.insert(45);

        // insert case 2: uncle is black and new node is a right child
        tree.insert(70);

        // insert case 3: uncle is black and new node is a left child
        tree.insert(9);

        // erase_fixup case 1: x sibling w Red
        tree.erase(42);

        // erase_fixup case 2: x sibling w Black, w->left and w->right Black
        tree.erase(50);

        // erase_fixup case 3: x sibling w Black, w->left Red, w->right Black
        tree.erase(45);

        // erase_fixup case 4: x sibling w Black, w->right Red
        tree.erase(16);

        // insert duplicate node
        tree.insert(88);

        // erase no existing node
        tree.erase(0);

        tree.make_graph();

        ft::rbtree<int>::iterator it = tree.end();

        std::cout << (*(--it)).key << std::endl;
        std::cout << "min: " << (*(tree.min(tree.root()))).key << std::endl;
        std::cout << "max: " << (*(tree.max(tree.root()))).key << std::endl;
    }

    */

    // min() test
//    {
//        ft::rbtree<int> tree;
//
//        //assert(tree.min(tree.root()) == tree.sentinel());
//
//        for (int i = 10; i > 0; i--)
//        {
//            tree.insert(i);
//            assert(tree.min(tree.root())->key == i);
//        }
//    }

    // max() test
//    {
//        ft::rbtree<int> tree;
//
//        //assert(tree.max(tree.root()) == tree.sentinel());
//
//        for (int i = 0; i < 10; i++)
//        {
//            tree.insert(i);
//            assert(tree.max(tree.root())->key == i);
//        }
//    }

//    {
//        // undefined behavior
//        std::map<int,int>::iterator it;
//        *it;
//    }

//    {
//        ft::rbtree<int> a;
//
//        a.insert(5);
//        a.insert(9);
//        a.insert(2);
//        a.insert(8);
//        a.insert(6);
//
//        ft::rbtree<int>::iterator it = a.begin();
//        ft::rbtree<int>::iterator ite = a.end();
//
//        if (it == ite) { }
//        if (it != ite) { }
//
//        (void)it;
//        (void)ite;
//
//      //  for (ft::rbtree<int>::iterator it = a.begin(); it != a.end(); it++)
//      //      std::cout << *it << std::endl;
//
//    }

//    {
//        ft::rbtree<int>::value_type value;
//        ft::rbtree<int>::key_type key;
//        ft::rbtree<int>::size_type size;
//        ft::rbtree<int>::pointer pointer;
//        ft::rbtree<int>::color_type color;
//
//        (void)value;
//        (void)key;
//        (void)size;
//        (void)pointer;
//        (void)color;
//    }

    return 0;
}
