#include <cassert>
#include <iostream>

#include "output_iterator.hpp"

/// @todo absolute paths
#include "../../include/utility/ft_pair.hpp"
#include "../utils.hpp"

// To use it, substitute `insert(tree.root(), i)' by 'insert(i)`
//#include "../../old_rb_tree.hpp"

// To use it, substitute `insert(i)' by 'insert(tree.root(), i)`
#include "rb_tree.hpp"
//#include "../../rbtree_no_sentinel.hpp"

///@note These 'tests' are not to be run at ft_containers evaluation.
///      Their purpose is to check for my own red black tree implementation if
///      every method is callable with a basic appropriate behavior. In-depth
///      comparative tests - real tests - will be applied to map container.
///      Since our map implementation heavily rely on our red black tree, the
///      utility of these 'tests' is to provide some basic insurance about the
///      latter before testing the first one.

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

/// @todo delete
void debug()
{
    {
        ft::rb_tree<int> tree;
        for (int i = 0; i < 18; i++) {
            tree.insert(i);
           // tree.insert(tree.root(), i);
            //tree.print(tree.root());
            std::cout << std::endl;
        }
    }
    {
        ft::rb_tree<int> tree;
        for (int i = 19; i > 0; i--) {
            tree.insert(i);
           // tree.insert(tree.root(), i);
           // tree.print(tree.root());
            std::cout << std::endl;
        }
    }
    {
        ft::rb_tree<int> tree;

        //tree.insert(tree.root(), 2);
        //tree.print(tree.root()); std::cout << std::endl;
        //tree.insert(tree.root(), 1);
        //tree.print(tree.root()); std::cout << std::endl;
        //tree.insert(tree.root(), 5);
        //tree.print(tree.root()); std::cout << std::endl;
        //tree.insert(tree.root(), 8);
        //tree.print(tree.root()); std::cout << std::endl;
        //tree.insert(tree.root(), 7);
        //tree.print(tree.root()); std::cout << std::endl;
        //tree.insert(tree.root(), 3);
        //tree.print(tree.root()); std::cout << std::endl;
        //tree.insert(tree.root(), 4);
        //tree.print(tree.root()); std::cout << std::endl;

        tree.insert(2);
        tree.insert(1);
        tree.insert(5);
        tree.insert(8);
        tree.insert(7);
        tree.insert(3);
        tree.insert(4);
    }
}

/****** Utility ***************************************************************/

template <typename Tree>
void min_test()
{
    Tree tree;

    //assert(tree.min(tree.root()) == NULL);
    //assert(tree.min(tree.root()) == tree.sentinel());

    for (int i = 10; i > 0; i--)
    {
        typename Tree::key_type key = key_type<Tree>(i);
        tree.insert(key);
        assert(tree.min(tree.root()) && tree.min(tree.root())->key == key);
    }
    log("min");
}

template <typename Tree>
void max_test()
{
    Tree tree;

   // assert(tree.min(tree.root()) == NULL);
    //assert(tree.min(tree.root()) == tree.sentinel());

    for (int i = 0; i < 10; i++)
    {
        typename Tree::key_type key = key_type<Tree>(i);
        tree.insert(key);
        assert(tree.min(tree.root()) && tree.max(tree.root())->key == key);
    }
    log("max");
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
    typename Tree::value_type i(key_type<Tree>(1));
    typename Tree::value_type j(key_type<Tree>(2));
    {
        // from empty
        Tree a;
        Tree b(a);
        assert(a == b);
    }
    {
        // from non-empty
        Tree a;
        a.insert(i);
        a.insert(j);
        Tree b(a);
        assert(a == b);
    }
    log("constructor by copy");
}

template <typename Tree>
void constructor_by_iterator_range_test()
{
    typename Tree::value_type i(key_type<Tree>(1));
    typename Tree::value_type j(key_type<Tree>(2));
    {
        // empty range
        Tree a;
        Tree b(a.begin(), a.end());
        assert(a == b);
    }
    {
        // non-empty range
        Tree a;
        a.insert(i);
        a.insert(j);
        Tree b(a.begin(), a.end());
        assert(a == b);
    }
    log("constructor by iterator range");
}

template <typename Tree>
void constructors_tests()
{
    std::cout << "== Constructors ==" << std::endl;
    constructor_by_default_test<Tree>();
    constructor_by_copy_test<Tree>();
    constructor_by_iterator_range_test<Tree>();
}

/****** Capacity test *********************************************************/

/// @todo add by copy and by range tests
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

/// @todo add by copy and by range tests
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
    std::cout << "== Capacity ==" << std::endl;
    empty_test<Tree>();
    size_test<Tree>();
}

/****** Accessors test ********************************************************/

/// @todo remove logs
template <typename Tree>
void find_test()
{
    Tree t;

    typename Tree::key_type k = key_type<Tree>(42);
    typename Tree::key_type l = key_type<Tree>(21);

    assert(t.find(k) == t.end());
    t.insert(k);
   // std::cout << *t.find(k) << std::endl;
   // std::cout << *t.end() << std::endl;
    assert(t.find(k) != t.end());

    assert(t.find(l) == t.end());
    t.insert(l);
    assert(t.find(l) != t.end());

    log("find");
}

template <typename Tree>
void accessors_tests()
{
    std::cout << "== Accessors ==" << std::endl;
    find_test<Tree>();
}

/****** Modifiers tests *******************************************************/

/// @todo insert cases not well tested
template <typename Tree>
void insert_test()
{
    typedef typename Tree::value_type value_type;
    value_type k(key_type<Tree>(42));
    value_type l(key_type<Tree>(21));
    {
        // single element (1)
        Tree t;
        t.insert(k);
        t.insert(l);

        Tree tree;
        tree.insert(value_type(key_type<Tree>(50)));
        tree.insert(value_type(key_type<Tree>(79)));
        tree.insert(value_type(key_type<Tree>(21)));
        tree.insert(value_type(key_type<Tree>(88)));
        tree.insert(value_type(key_type<Tree>(16)));
        tree.insert(value_type(key_type<Tree>(67)));
        tree.insert(value_type(key_type<Tree>(10)));
        tree.insert(value_type(key_type<Tree>(19)));
        tree.insert(value_type(key_type<Tree>(11)));
        tree.insert(value_type(key_type<Tree>(42)));
        tree.insert(value_type(key_type<Tree>(27)));
        tree.insert(value_type(key_type<Tree>(90)));
        tree.insert(value_type(key_type<Tree>(55)));

        // insert case 1: uncle is red
        tree.insert(value_type(key_type<Tree>(45)));

        // insert case 2: uncle is black and new node is a right child
        tree.insert(value_type(key_type<Tree>(70)));

        // insert case 3: uncle is black and new node is a left child
        tree.insert(value_type(key_type<Tree>(9)));

        // insert duplicate node
        tree.insert(value_type(key_type<Tree>(42)));
    }
    {
        // with hint (2)
        /// @todo add some statements ?
        Tree tree;
        tree.insert(tree.begin(), k);
        tree.insert(tree.begin(), l);
    }
    {
        // by range (3)
        /// @todo add some statements ?
        Tree t, u;
        t.insert(k);
        t.insert(l);
        assert(t != u);
        u.insert(t.begin(), t.end());
        assert(t == u);
    }
    log("insert");
}

/// @todo add more tests
template <typename Tree>
void erase_test()
{
    {
        // by iterator position
        Tree a, b;
        assert(a == b);
        a.insert(typename Tree::value_type());
        assert(a != b);
        a.erase(a.begin());
        assert(a == b);
    }
    {
        // by key
        Tree a, b;
        assert(a == b);
        a.insert(typename Tree::value_type());
        assert(a != b);
        a.erase(typename Tree::value_type().key);
        assert(a == b);
    }
    {
        // by iterator range
        Tree a, b;
        assert(a == b);
        a.insert(typename Tree::value_type());
        assert(a != b);
        a.erase(a.begin(), a.begin());
        assert(a != b);
        a.erase(a.begin(), a.end());
        assert(a == b);
    }
    log("erase");
}

template <typename Tree>
void modifiers_tests()
{
    std::cout << "== Modifiers ==" << std::endl;
    insert_test<Tree>();
    erase_test<Tree>();
}

/****** Operators tests *******************************************************/

template <typename Tree>
void equal_test()
{
    /// @note This is important because right hand side Tree has to be const
    { assert(Tree() == Tree()); }

    {
        Tree a, b;
        typename Tree::key_type k = key_type<Tree>(42);
        typename Tree::key_type l = key_type<Tree>(21);

        assert(a == b);

        a.insert(k);
        b.insert(k);
        assert(a == b);

        a.insert(l);
        b.insert(l);
        assert(a == b);
    }

    log("operator==");
}

template <typename Tree>
void not_equal_test()
{
    {
        Tree a, b;
        typename Tree::key_type k = key_type<Tree>(42);
        typename Tree::key_type l = key_type<Tree>(21);

        a.insert(k);
        assert(a != b);
        b.insert(k);

        a.insert(l);
        assert(a != b);
        b.insert(l);
    }

    log("operator!=");
}

/// @todo
template <typename Tree>
void operators_tests()
{
    std::cout << "== Operators ==" << std::endl;
    equal_test<Tree>();
    not_equal_test<Tree>();
}

/****** Tree tests ************************************************************/

template <typename T>
void tree_test()
{
//    constructors_tests<ft::rb_tree<T>>();
//    capacity_tests<ft::rb_tree<T>>();
//    accessors_tests<ft::rb_tree<T>>();
//    modifiers_tests<ft::rb_tree<T>>();
//    operators_tests<ft::rb_tree<T>>();

    /// @note this won't compile since `operator*` doesn't return a `value_type`
//    iterator_test<ft::rb_tree<T>>();

//    /// @todo (?)
//    // allocator_tests<ft::rb_tree<T>>();

//    min_test<ft::rb_tree<T>>();
//    max_test<ft::rb_tree<T>>();
}

/****** Main ******************************************************************/

int main()
{
//    debug();

//    tree_test<A>();
    tree_test<int>();
//    tree_test<ft::pair<const int,int>>();

    // everything below segfault

//    {
//        ft::rb_tree<int>::iterator it;
//        ++it;
//        int x = *it;
//        (void)x;
//        std::cout << *it  << std::endl;
//    }

//    {
//        std::map<int,int>::iterator it;
//        std::map<int,int>::value_type x = *it;
//        std::map<int,int>::iterator it2 = ++it;
//        (void)x;
//        (void)it2;
//    }

//    {
//        std::map<int,int> m;
//        std::map<int,int>::iterator it = m.begin();
//
//        std::map<int,int>::iterator it2 = --it;
//        (void)it2;
//    }

    return 0;
}