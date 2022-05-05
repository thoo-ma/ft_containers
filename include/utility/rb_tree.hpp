#ifndef RB_TREE_HPP
#define RB_TREE_HPP 1

#include <stddef.h> // NULL
#include <iostream> // std::ostream
#include <memory> // std::allocator

namespace ft {

template <typename T>
class rb_node
{
    public:

    typedef T	                key_type;
    typedef enum { Black, Red } color_type;

    // private ?
    key_type    key;
    color_type  color;
    rb_node * 	left;
    rb_node *	right;
    rb_node *	parent;

    rb_node(key_type const & val)
    : key(val), color(Black), left(NULL), right(NULL), parent(NULL)
    { }

//    rb_node<key_type> &
//    operator=(const rb_node<key_type> & a)
//    {
//        key = a.key;
//        color = a.color;
//        left = a.left;
//        right = a.right;
//        parent = a.parent;
//        return *this;
//    }

};

template <typename T>
std::ostream &
operator<<(std::ostream & o, rb_node<T> const & node)
{ o << node.key; return o;}

template <typename T, typename Allocator = std::allocator<rb_node<T>>>
class rb_tree {

    /*
     *	RULES
     * 	_____
     *
     * 	1. Every node is Red or Black (Color property)
     * 	2. Every null node is considered Black (Null property)
     * 	3. A Red node does not have a Red child (Red  proterty)
     * 	4. Every path from a given node to any of its descendant null nodes
     *    goes through the same number of black nodes. (Black property)
     *
     *	OPERATIONS
     *	__________
     *
     *	- search
     *	- insert
     *	- delete
     *
     *	GLOSSARY
     *	________
     *
     *  - path
     *  - leaf: null node
     *	- node's black depth: number of black nodes from root to that node
     *	- tree's black height: number of black nodes in any path from root to leaves
     *
     *	cf. https://en.wikipedia.org/wiki/Red%E2%80%93black_tree#Properties
     *
     */

    /****** Member types ******************************************************/

    public:

    typedef T	            key_type;
    typedef Allocator       allocator_type;
    typedef rb_node<T>	    value_type;
    typedef rb_node<T> *	pointer;

    /****** Internal data *****************************************************/

    private:

    value_type *     _root;
    allocator_type	_alloc;

    void _print(value_type * node) const
    {
        if (node == NULL) return;
        if (node->left)
            _print(node->left);
        if (node->right)
            _print(node->right);
        std::cout << node->key << std::endl;
    }

    /****** Member functions **************************************************/

    public:

    rb_tree() : _root(NULL) { }
    //rb_tree(const rb_tree & tree) { }

    ~rb_tree() {}

    void print() const
    { return _print(_root); }

    void insert(const key_type & val)
    {
        pointer tmp = _alloc.allocate(1);
        _alloc.construct(tmp, val);
        if (_root == NULL)
            _root = tmp;
    }
};

} // namespace

#endif /* RB_TREE_HPP */
