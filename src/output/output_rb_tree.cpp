#include <map> // ??
#include <vector> // delete
#include <cassert>
#include <type_traits> // std::is_same

#include "rb_tree.hpp"
#include "ft_pair.hpp" // delete
#include "ft_vector.hpp" // delete
#include "../utils/colors.hpp" // put into log
#include "output_iterator.hpp"

///@note These 'tests' are not to be run at ft_containers evaluation.
///      Their purpose is to check for my own red black tree implementation if
///      every method is callable with a basic appropriate behavior. In-depth
///      comparative tests - real tests - will be applied to map container.
///      Since our map implementation heavily rely on our red black tree, the
///      utility of these 'tests' is to provide some basic insurance about the
///      latter before testing the first one.

/****** Log *******************************************************************/

inline void log(std::string s)
{
    std::cout << s << GREEN << " OK" << RESET << std::endl;
}

/****** Node ******************************************************************/

void node_test()
{
    {
        ft::rb_tree<int>::value_type a;
        ft::rb_tree<int>::value_type b;

        assert(a.key == 0);
        assert(b.key == 0);

        a.key = 42;
        b = a;

        assert(a.key == 42);
        assert(b.key == 42);

        ft::rb_tree<int>::value_type c(42);

        assert(c.key == a.key);
    }
}

/****** Debug *****************************************************************/

void debug()
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
}

/****** Utility ***************************************************************/

void min_test()
{
    ft::rb_tree<int> tree;

    assert(tree.min(tree.root_node()) == NULL);

    for (int i = 10; i > 0; i--)
    {
        tree.insert(tree.root_node(), i);
        assert(tree.min(tree.root_node()) && tree.min(tree.root_node())->key == i);
    }

}

void max_test()
{
    ft::rb_tree<int> tree;

    assert(tree.min(tree.root_node()) == NULL);

    for (int i = 0; i < 10; i++)
    {
        tree.insert(tree.root_node(), i);
        assert(tree.min(tree.root_node()) && tree.max(tree.root_node())->key == i);
    }

}

/****** Constructors test *****************************************************/

template <typename Tree>
void constructor_by_default_test()
{
    Tree a;

    assert(a.empty());
    assert(a.size() == 0);

    log("constructor by default");
}

template <typename Tree>
void constructor_by_copy_test()
{
    {
        // from empty
        Tree a;
        Tree b(a);
        assert(a == b);
    }
    {
        // from non-empty
        Tree a;
        a.insert(typename Tree::value_type());
        Tree b(a);
        assert(a == b);
    }
    log("constructor by copy");
}

template <typename Tree>
void constructor_by_iterator_range_test()
{
    {
        // empty range
        Tree a;
        Tree b(a.begin(), a.end());
        assert(a == b);
    }
    {
        // non-empty range
        Tree a;
        a.insert(typename Tree::value_type());
        Tree b(a.begin(), a.end());
        assert(a == b);
    }
    log("constructor by iterator range");
}

template <typename Tree>
void constructors_tests()
{
    constructor_by_default_test<Tree>();
    constructor_by_copy_test<Tree>();
    constructor_by_iterator_range_test<Tree>();
}

/****** Capacity test *********************************************************/

template <typename Tree>
void empty_test()
{
    Tree t;
    {
        // by default
        assert(t.empty());
    }
    {
        // by copy
        assert(Tree(t).empty());
    }
    {
        // by iterator range
        assert(Tree(t.begin(), t.end()).empty());
    }
    log("empty");
}

template <typename Tree>
void size_test()
{
    {
        // constructed by default
        assert(Tree().size() == 0);
    }
    {
        // constructed by copy
        Tree a, b;
        b.insert(typename Tree::value_type());
        assert(a.size() != b.size());
        assert(Tree(a).size() == a.size());
        assert(Tree(b).size() == b.size());
    }
    {
        // constructed by iteratior range
        Tree a, b;
        b.insert(typename Tree::value_type());
        assert(a.size() != b.size());
        assert(Tree(a.begin(), a.end()).size() == a.size());
        assert(Tree(b.begin(), b.end()).size() == b.size());
    }
    log("size");
}

template <typename Tree>
void capacity_tests()
{
    empty_test<Tree>();
    size_test<Tree>();
}

/****** Accessors test ********************************************************/

template <typename Tree>
void find_test()
{
    Tree t;

    typename Tree::key_type k(42);
    typename Tree::key_type l(21);

    assert(t.find(k) == NULL);
    t.insert(k);
    assert(t.find(k) != NULL);

    assert(t.find(l) == NULL);
    t.insert(l);
    assert(t.find(l) != NULL);

    log("find");
}

template <typename Tree>
void accessors_tests()
{
    find_test<Tree>();
}

/****** Modifiers tests *******************************************************/

template <typename Tree>
void insert_test()
{
    typename Tree::key_type k(42);
    typename Tree::key_type l(21);
    {
        // single element (1)
        Tree t;
        t.insert(k);
        t.insert(l);
    }
    {
        // with hint (2)
        Tree t;
        t.insert(t.begin(), k);
        t.insert(t.begin(), l);
    }
    {
        // by range (3)
        Tree t, u;
        t.insert(k);
        t.insert(l);
        u.insert(t.begin(), t.end());
        assert(t == u);
    }
    log("insert");
}

template <typename Tree>
void erase_test()
{
    {
        // by iterator position
        Tree a, b;
        assert(a == b);
        a.insert(typename Tree::key_type(42));
        assert(a != b);
        a.erase(a.begin());
        assert(a == b);
    }
    {
        // by key
    }
    {
        // by iterator range
    }
    log("erase");
}

template <typename Tree>
void modifiers_tests()
{
//    insert_test<Tree>();
    erase_test<Tree>();
}

/****** Tree tests ************************************************************/

template <typename T>
void tree_test()
{
//    constructors_tests<ft::rb_tree<T>>();
//    capacity_tests<ft::rb_tree<T>>();
//    accessors_tests<ft::rb_tree<T>>();

    // allocator_tests<ft::rb_tree<T>>();

    modifiers_tests<ft::rb_tree<T>>();
    // operators_tests<ft::rb_tree<T>>();
    // iterators_tests(); // TODO

/// @note this tests are not possible
//  iterator_test<ft::rb_tree<int>>();
//  iterator_test<ft::rb_tree<double>>();
}

/****** Main ******************************************************************/

int main()
{
//    debug();
//    min_test();
//    max_test();

//    tree_test<int>();

    {
        ft::rb_tree<int> tree;

        std::cout << "-- insertion --" << std::endl;
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

        std::cout << "-- deletion --" << std::endl;
   //     tree.erase(2);
   //     tree.print(tree.root_node()); std::cout << std::endl;

    }

    return 0;
}
