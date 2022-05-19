#ifndef RB_TREE_HPP
#define RB_TREE_HPP 1

#include <stddef.h> // NULL
#include <iostream> // std::ostream
#include <memory> // std::allocator

namespace ft {

template <typename T,
          typename Compare = std::less<T>
//          typename Allocator = std::allocator<struct node>
>
class rb_tree
{
    /****** Member types ******************************************************/

    public:

    struct node; // forward declaration

    typedef struct node	                node_type; // value_type ?
    typedef struct node *	            pointer;
    typedef struct node &               reference;
    typedef T	                        key_type;
    typedef Compare	                    compare;
    typedef std::allocator<struct node>	allocator_type;
    typedef enum { Black, Red }	        color_type;

    struct node
    {
        key_type	key;
        color_type	color;
        pointer     left;
        pointer     right;
        pointer     parent;

        node(const key_type & key = key_type())
        : key(key), color(Red), left(NULL), right(NULL), parent(NULL) { }

    };

    /****** Private variables *************************************************/

    private:

    pointer         _root;
    compare	        _comp;
    allocator_type	_alloc;

    /****** Private functions *************************************************/

    // utility for recursive fashion destructor
    void _destroy(const pointer node)
    {
        if (node == NULL)
            return;
        _destroy(node->left);
        _destroy(node->right);
        _alloc.destroy(node);
        _alloc.deallocate(node, 1);
    }

    pointer _get_brother(pointer node)
    {
        return node == node->parent->left
        ? node->parent->right
        : node->parent->left;
    }

    void left_rotate(pointer node)
    {
        if (node->right)
        {
            if (node->parent)
            {
                node->parent->left == node
                ? node->parent->left = node->right
                : node->parent->right = node->right;
            }
            node->right->parent = node->parent;
            node->parent = node->right;
            node->right = node->right->left;
            node->parent->left = node;
            if (node == _root)
                _root = node->parent;
        }
    }

    void right_rotate(pointer node)
    {
        if (node->left)
        {
            if (node->parent)
            {
                node->parent->left == node
                ? node->parent->left = node->left
                : node->parent->right = node->left;
            }
            node->left->parent = node->parent;
            node->parent = node->left;
            node->left = node->left->right;
            node->parent->right = node;
            if (node == _root)
                _root = node->parent;
        }
    }

    void left_balance(pointer node, pointer parent, pointer uncle)
    {
        // case 1: uncle is Red
        if (uncle && uncle->color == Red)
        {
            uncle->color = Black;
            parent->color = Black;
            parent->parent->color = Red;
        }
        else
        {
            // case 3: node is right-child of parent
            if (node == parent->right)
                left_rotate(parent);
            // case 2: node is left-child of parent
            right_rotate(parent->parent);
            node->parent->color = Black;
            node->parent->right->color = Red;
        }
    }

    void right_balance(pointer node, pointer parent, pointer uncle)
    {
        // case 1: uncle is Red
        if (uncle && uncle->color == Red)
        {
            uncle->color = Black;
            parent->color = Black;
            parent->parent->color = Red;
        }
        else
        {
            // case 3: node is right-child of parent
            if (node == parent->right)
                right_rotate(parent);
            // case 2: node is left-child of parent
            left_rotate(parent->parent);
            node->parent->color = Black;
            node->parent->left->color = Red;
        }
    }

    /****** Member functions **************************************************/

    public:

    // utility (might delete later)
    pointer * root_ptr() { return &_root; }
    pointer & root_ref() { return  _root; }
    pointer  root_node() { return  _root; }

    // utility (might delete later)
    void print(const pointer node)
    {
        if (node == NULL)
            return;

        node->color == Red
        ? std::cout << "\33[31m" << node->key << "\33[0m"
        : std::cout << "\33[30m" << node->key << "\33[0m";

        if (node->left || node->right)
        {
            std::cout << '(';
            print(node->left);
            if (node->right)
            {
                std::cout << ',';
                print(node->right);
            }
            std::cout << ')';
        }
    }

    rb_tree() : _root(NULL), _comp(compare()), _alloc(allocator_type()) { }

    //rb_tree(const rb_tree & tree) { (void)tree; }

    // for-loop fashion
    ~rb_tree()
    {
        pointer	    node;
        pointer     parent;

        node = _root;
        while (node)
        {
            parent = node->parent;
            while (node && node->left)
            {
                parent = node;
                node = node->left;
            }
            if (node && node->right)
            {
                parent = node;
                node = node->right;
            }
            if (node && node->left == NULL && node->right == NULL)
            {
                _alloc.destroy(node);
                _alloc.deallocate(node, 1);
                if (parent && node == parent->left) parent->left = NULL;
                if (parent && node == parent->right) parent->right = NULL;
                node = parent;
            }
        }
    }

    // recursive fashion
    //~rb_tree() { _destroy(_root); }

    void delete_node(pointer node)
    {
        // case 1: node has no right child
        if (node->right == NULL)
        {
            if (node->parent)
            {
                node->parent->left == node
                ? node->parent->left = node->left
                : node->parent->right = node->left;
            }
            if (node->left)
                node->left->parent = node->parent;
            // not sure
            _alloc.destroy(node);
            _alloc.deallocate(node);
            return;
        }

        // case 2: node's right child has no left child
        if (node->right->left == NULL)
        {
            if (node->parent)
            {
                node->parent->left == node
                ? node->parent->left = node->right
                : node->parent->right = node->right;
            }
            node->right->parent = node->parent;
            node->right->left = node->left;
            if (node->left)
                node->left->parent = node->right;
            // not sure
            _alloc.destroy(node);
            _alloc.deallocate(node);
        }

        // case 3: node's right child has a left child
        else
        {
            // find inorder sucecssor
            pointer succ = node->right->left;
            while (succ->left) { succ = succ->left; }

            // delete succ
            succ->parent->left = succ->right;
            if (succ->right)
                succ->right->parent = succ->parent;

            // replace node by succ
            node->key = succ->key;

            // not sure
            _alloc.destroy(node);
            _alloc.deallocate(node);
        }
    }

    // with a recursive fashion search
    void insert(pointer & node, pointer parent, key_type & key)
    {
        // insert at leaf -- or root
        if (node == NULL)
        {
            // allocate & construct `node` from `key`
            node = _alloc.allocate(1);
            _alloc.construct(node, node_type(key));
            // insert `node` below `parent`
            node->parent = parent;
            if (parent)
            {
                key < parent->key
                ? parent->left = node
                : parent->right = node;
            }
            else return;
            // rebalance
            while (parent->parent && parent->color == Red)
            {
                node == parent->left
                ?  left_balance(node, parent, _get_brother(parent))
                : right_balance(node, parent, _get_brother(parent));
            }
            _root->color = Black;
            return;
        }
        // recursive until leaf
        return key < node->key
        ? insert(node->left, node, key)
        : insert(node->right, node, key);
    }

    // recursive fashion
    // This Red Black Tree support duplicate keys.
    // This function return the first equivalent key when there are.
    pointer find(const pointer node, const key_type & key) const
    {
        if (node == NULL || node->key == key)
            return node;
        return key < node->key
        ? find(node->left, key)
        : find(node->right, key);
    }

};

} // namespace

#endif /* RB_TREE_HPP */
