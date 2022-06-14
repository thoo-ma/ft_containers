#ifndef RB_TREE_HPP
#define RB_TREE_HPP 1

#include <stddef.h> // NULL
#include <iostream> // std::ostream
#include <memory> // std::allocator

// TODO
// - inline function or macro to replace ternaries
// - handle allocator failure

namespace ft {

template <typename T,
          typename Compare = std::less<T>
//          typename Allocator = std::allocator<struct node>
>
class rb_tree
{
    /**************************************************************************/
    /*                                                                        */
    /*      Member types                                                      */
    /*                                                                        */
    /**************************************************************************/

    public:

    struct node; // forward declaration

    typedef struct node	                node_type; // value_type ?
    typedef struct node *	            pointer;
    typedef struct node &               reference;
    typedef size_t	                    size_type;
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

        node(const node_type & node)
        : key(node.key), color(node.color), left(NULL), right(NULL), parent(NULL) { }

      //  node(const node_type & node) { *this = node; }

        struct node & operator=(const struct node & a)
        {
            this->key = a.key;
            this->color = a.color;
            return *this;
        }

    };

    /**************************************************************************/
    /*                                                                        */
    /*      Private variables                                                 */
    /*                                                                        */
    /**************************************************************************/

    private:

    pointer         _root;
    size_type	    _size;
    compare	        _comp;
    allocator_type	_alloc;

    /**************************************************************************/
    /*                                                                        */
    /*      Private functions                                                 */
    /*                                                                        */
    /**************************************************************************/

    // utility for recursive fashion destructor
    void _destroy(pointer const node)
    {
        if (node == NULL)
            return;
        _destroy(node->left);
        _destroy(node->right);
        _alloc.destroy(node);
        _alloc.deallocate(node, 1);
    }

    // TODO
    pointer _get_brother(pointer const node)
    {
        return node == node->parent->left
        ? node->parent->right
        : node->parent->left;
    }

    // recursive fashion
    pointer _copy(node_type * src, node_type * parent)
    {
        node_type * dst;

        if (src == NULL)
            return NULL;

        dst = _alloc.allocate(1);
        _alloc.construct(dst, *src);

        if (parent)
            dst->parent = parent;

        dst->left = _copy(src->left, dst);
        dst->right = _copy(src->right, dst);

        return dst;
    }

    // iterative fashion
    pointer _copy(node_type * src)
    {
        node_type * dst;
        node_type * dst_root;

        if (src == NULL)
            return NULL;
//        _allocate_and_copy(dst, src);
        dst_root = _alloc.allocate(1);
        _alloc.construct(dst_root, *src);
        dst = dst_root;
        while (1)
        {
            while (src->left)
            {
                dst->left = _alloc.allocate(1);
                _alloc.construct(dst->left, *src);
                dst->left->parent = dst;
                src = src->left;
                dst = dst->left;
            }
            dst->left = NULL;
            while (1)
            {
                if (src->right)
                {
                    dst->right = _alloc.allocate(1);
                    _alloc.construct(dst->right, *src);
                    dst->right->parent = dst;
                    src = src->right;
                    dst = dst->right;
                    break;
                }
                else
                    dst->right = NULL;
                while (1)
                {
                    node_type * tmp = src;

                    src = src->parent;
                    if (src == NULL)
                        return dst_root;
                    dst = dst->parent;
                    if (tmp == src->left)
                        break;
                }
            }
        }
    }

    /**************************************************************************/
    /*                                                                        */
    /*      Member functions                                                  */
    /*                                                                        */
    /**************************************************************************/

    public:

    /****** Utility (might delete later) **************************************/

    pointer * root_ptr() { return &_root; }
    pointer & root_ref() { return  _root; } // !const bc used into map[]
    pointer  root_node() const { return  _root; }

    void print(const pointer node)
    {
        if (node == NULL)
            return;

        node->color == Red
        ? std::cout << "\33[31m" << node->key << "\33[0m"
        : std::cout << "\33[37m" << node->key << "\33[0m";

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

    rb_tree & operator=(const rb_tree & tree)
    {
        _root = _copy(tree._root, NULL);
        //_root = _copy(tree._root);
        return *this;
    }

    /****** Constructors ******************************************************/

    rb_tree()
    : _root(NULL), _size(0), _comp(compare()), _alloc(allocator_type()) { }

    rb_tree(const rb_tree & tree)
    : _root(NULL), _size(tree._size), _comp(tree._comp), _alloc(tree._alloc)
    { *this = tree; }
    //{ _root = _copy(tree._root, NULL); }

    /****** Destructor ********************************************************/

    // iterative fashion
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

    /****** Capacity **********************************************************/

    //size_type height() const { return _height; } // TODO ?
    size_type size() const { return _size; }

    /****** Element access ****************************************************/

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

    /****** Modifiers *********************************************************/

    // with a recursive fashion search -- BUG
    void insert(pointer * const node, pointer * const parent, key_type & key)
    {
        // insert at leaf -- or root
        if (*node == NULL)
        {
            // allocate & construct `node` from `key`
            *node = _alloc.allocate(1);
            _alloc.construct(*node, node_type(key));
            _size++;
            // insert `node` below `parent`
            if (parent == NULL)
            {
                (*node)->parent = NULL;
                return;
            }
            (*node)->parent = *parent;
            if (*parent)
            {
                key < (*parent)->key
                ? (*parent)->left = *node
                : (*parent)->right = *node;
            }
            else return;
            // rebalance
            while (*parent && (*parent)->parent && (*parent)->color == Red)
            {
                *node == (*parent)->left
                ?  _left_balance(node, parent, _get_brother(*parent))
                : _right_balance(node, parent, _get_brother(*parent));
            }
            _root->color = Black;
            return;
        }
        // recursive until leaf
        return key < (*node)->key
        ? insert(&(*node)->left, node, key)
        : insert(&(*node)->right, node, key);
    }

    // with an iterative fashion search
    void insert(pointer node, key_type key)
    {
        // parent of the new node
        pointer parent = NULL;

        // find leaf where to insert new node
        while (1) // while (node)
        {
            if (node == NULL) // remove
                break;
            if (key == node->key)
                return;
            while (node && key < node->key)
            {
                parent = node;
                node = node->left;
            }
            while (node && key > node->key)
            {
                parent = node;
                node = node->right;
            }
        }

        // alloc and construct new node
        pointer new_node = _alloc.allocate(1);
        _alloc.construct(new_node, node_type(key));

        // update size
        _size++;

        // insert parent above new node
        new_node->parent = parent;

        // new node is root: insertion complete
        if (parent == NULL)
        {
            _root = new_node;
            return;
        }

        // insert new node below its parent
        new_node->key < parent->key
        ? parent->left = new_node
        : parent->right = new_node;

        // rebalance
        while (parent && parent->parent && parent->color == Red)
        {
            // left-balance
            if (parent == parent->parent->left)
            {
                /*
                 * case 1: uncle is Red
                 *
                 *        B               R
                 *       / \             / \
                 *      R   R    ==>    B   B
                 *     / \             / \
                 *   (R   R)         (R   R)
                 *
                 */
                if (parent->parent->right && parent->parent->right->color == Red)
                {
                    parent->parent->left->color = Black;
                    parent->parent->right->color = Black;
                    parent->parent->color = Red;
                    parent = parent->parent->parent;
                }
                else
                {
                    /*
                     * case 3: node direction != parent direction
                     *
                     *       A                A
                     *      /                /
                     *     B       ==>      C
                     *    / \              / \
                     *   x   C            B   z
                     *      / \          / \
                     *     y   z        x   y
                     *
                     */
                    if (new_node == parent->right)
                    {
                        parent->parent->left = new_node;
                        new_node->parent = parent->parent;

                        parent->right = new_node->left;
                        if (parent->right)
                            parent->right->parent = parent;

                        new_node->left = parent;
                        parent->parent = new_node;

                        parent = new_node;
                        new_node = parent->left;
                    }
                    /*
                     *  case 2: now node direction == parent direction
                     *
                     *         A              C
                     *        /              / \
                     *       C      ==>     /   \
                     *      / \            B     A
                     *     B   z          / \   /
                     *    / \            x   y z
                     *   x   y
                     *
                     */
                    parent->parent->left = parent->right;
                    if (parent->right)
                        parent->right->parent = parent->parent;
                    parent->right = parent->parent;
                    if (parent->parent->parent)
                    {
                        parent->parent == parent->parent->parent->left
                        ? parent->parent->parent->left = parent
                        : parent->parent->parent->right = parent;
                    }
                    else
                        _root = parent;
                    parent->parent = parent->parent->parent;
                    parent->right->parent = parent;

                    parent->color = Black;
                    parent->right->color = Red;
                    break;
                }
            }
            // right-balance
            else
            {
                /*
                 * case 1: uncle is Red
                 *
                 *      B                R
                 *     / \              / \
                 *    R   R     ==>    B   B
                 *       / \              / \
                 *     (R   R)          (R   R)
                 *
                 */
                if (parent->parent->left && parent->parent->left->color == Red)
                {
                    parent->parent->left->color = Black;
                    parent->parent->right->color = Black;
                    parent->parent->color = Red;
                    parent = parent->parent->parent;
                }
                else
                {
                    /*
                     * case 3: node direction != parent direction
                     *
                     *    A              A
                     *     \              \
                     *      B     ==>      C
                     *     / \            / \
                     *    C   x          y   B
                     *   / \                / \
                     *  y   z              z   x
                     *
                     */
                    if (new_node == parent->left)
                    {
                        parent->parent->right = new_node;
                        new_node->parent = parent->parent;

                        parent->left = new_node->right;
                        if (parent->left)
                            parent->left->parent = parent;

                        new_node->right = parent;
                        parent->parent = new_node;

                        parent = new_node;
                        new_node = parent->right;
                    }
                    /*
                     *  case 2: now node direction == parent direction
                     *
                     *    A                   C
                     *     \                 / \
                     *      C      ==>      /   \
                     *     / \             A     B
                     *    y   B             \   / \
                     *       / \             y z   x
                     *      z   x
                     *
                     */
                    parent->parent->right = parent->left;
                    if (parent->left)
                        parent->left->parent = parent->parent;
                    parent->left = parent->parent;
                    if (parent->parent->parent)
                    {
                        parent->parent == parent->parent->parent->left
                        ? parent->parent->parent->left = parent
                        : parent->parent->parent->right = parent;
                    }
                    else
                        _root = parent;
                    parent->parent = parent->parent->parent;
                    parent->left->parent = parent;

                    parent->color = Black;
                    parent->left->color = Red;
                    break;
                }
            }
        }

        //
        _root->color = Black;
    }

    void erase(pointer node)
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
            _size--;
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
            _size--;
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
            _size--;
        }
    }

};

} // namespace

#endif /* RB_TREE_HPP */
