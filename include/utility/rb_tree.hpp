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
    typedef rb_node<T> *        pointer;

    // private ?
    key_type    key;
    color_type  color;
    rb_node * 	left;
    rb_node *	right;
    rb_node *	parent;

    rb_node(key_type const & val)
    : key(val), color(Black), left(NULL), right(NULL), parent(NULL)
    { }

//    rb_node(const key_type & key, const color_type & color,
//            pointer left, pointer right, pointer parent)
//    : key(key), color(color), left(left), right(right), parent(parent)
//    { }

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
bool
operator==(const rb_node<T> & lhs, const rb_node<T> rhs)
{ return lhs.key == rhs.key; }

template <typename T>
std::ostream &
operator<<(std::ostream & o, rb_node<T> const & node)
{ o << node.key; return o;}

template <typename T,
          //typename Compare = std::less<T>,
          typename Allocator = std::allocator<rb_node<T>>
>
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
     *	- search (lookup)
     *	- insert (6 cases)
     *	- delete (6 cases)
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
    typedef rb_node<T>	    node_type; // value_type ?
    typedef rb_node<T> *	pointer;
    typedef rb_node<T> &	reference;

    typedef enum { Left, Right } direction;
    typedef enum { Black, Red } color_type;

    /****** Internal data *****************************************************/

    private:

    pointer         _root;
    allocator_type	_alloc;

    void _print(pointer node) const
    {
        if (node == NULL) return;
        if (node->left)
            _print(node->left);
        if (node->right)
            _print(node->right);
        std::cout << node->key << std::endl;
    }

    void	_debug_insert(pointer node) const
    {
        std::cout << "inserted node key: " << node->key << std::endl;
        std::cout << "inserted node color: " << node->color << std::endl;
        std::cout << "inserted node parent: " << node->parent << std::endl;
        if (node->parent)
        {
            node == node->parent->left
            ? std::cout << "inserted node directon: left" << std::endl
            : std::cout << "inserted node directon: right" << std::endl;
        }
        else { std::cout << "inserted node directon: root" << std::endl; }
    }

    /****** Member functions **************************************************/

    public:

    pointer & root() { return _root; }

    rb_tree() : _root(NULL) { }

    rb_tree(const rb_tree & tree) { (void)tree; }

    // inline ? macro ?
    direction get_dir(reference node) const
    { return node == node->parent->left ? Left : Right; }

    ~rb_tree()
    {
        pointer	    node;
        pointer     parent;
        direction	dir;

        node = _root;
        dir = Left;
        while (node)
        {
            parent = node->parent;
            while (node && node->left)
            {
                dir = Left;
                parent = node;
                node = node->left;
            }
            if (node && node->right)
            {
                dir = Right;
                parent = node;
                node = node->right;
            }
            if (node && node->left == NULL && node->right == NULL)
            {
                _alloc.destroy(node);
                _alloc.deallocate(node, 1);
                node = parent;
                if (node) { dir == Left ? node->left = NULL : node->right = NULL; }
            }
        }
    }

    void print() const { return _print(_root); }

    key_type insert(pointer & node, pointer & parent, const key_type & key)
    {
        // insert
        if (node == NULL)
        {
            pointer tmp = _alloc.allocate(1);
            // insert at root
            if (node == _root)
            {
                _alloc.construct(tmp, key);
                _root = tmp;
            }
            // insert at leaf
            else
            {
                _alloc.construct(tmp, key);
                // udate parent.left or parent.right
                tmp->parent = parent;
                // fix this cast (only one enum), rb_node as subclass (or maybe coloring into constructor)
                tmp->color = static_cast<typename rb_node<T>::color_type>(Red);
                node = tmp;
                // case 1
           //     if ((*parent)->color == Black) { return key; } // insertion complete
           //     if ((*parent)->parent == NULL) { (*parent)->color = Red; return; } // case 4. insertion complete
            }
            _debug_insert(node);
            return key;
        }
        // recursive until leaf
        return key < node->key
        ? insert(node->left, node, key)
        : insert(node->right, node, key);
    }

    // Since rb_tree support duplicate keys, what do we return ? 1st one or all equivalent keys ?
    pointer find(pointer node, const key_type & key) const
    {
        if (node == _root)
            return NULL;
        if (node->key == key)
            return node;

    }

};

} // namespace

#endif /* RB_TREE_HPP */
