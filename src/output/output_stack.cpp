#include <stack>
#include <deque>
#include <vector>
#include <cassert>
#include <iostream>
#include <stdexcept>

#include "ft_stack.hpp"
#include "ft_vector.hpp"

class Foo { };

/****** Constructor test ******************************************************/

template <typename T>
void stack_constructor_test()
{
    // implicit underlying container constructed by default
    assert(ft::stack<T>().size() == 0);
    assert(std::stack<T>().size() == 0);

    // explicit underlying container constructed by default
    assert((ft::stack<T, ft::vector<T>>()).size() == 0);
    assert((std::stack<T, std::deque<T>>()).size() == 0);
    assert((std::stack<T, std::vector<T>>()).size() == 0);

    // implicit underlying container constructed by fill
    assert(ft::stack<T>(ft::vector<T>(10, T())).size() == 10);
    assert(std::stack<T>(std::deque<T>(10, T())).size() == 10);

    // explicit underlying container constructed by fill
    assert((ft::stack<T, ft::vector<T>>(ft::vector<T>(10, T()))).size() == 10);
    assert((std::stack<T, std::deque<T>>(std::deque<T>(10, T()))).size() == 10);
}

/****** Empty test ************************************************************/

template <typename T>
void stack_empty_test()
{
    // underlying container constructed by default
    assert(ft::stack<T>().empty());
    assert(std::stack<T>().empty());

    // underlying container constructed with size 0
    assert((ft::stack<T>(ft::vector<T>(0))).empty());
    assert((std::stack<T>(std::deque<T>(0))).empty());

    // underlying container constructed with size > 0
    assert(!(ft::stack<T>(ft::vector<T>(10))).empty());
    assert(!(std::stack<T>(std::deque<T>(10))).empty());
}

/****** Push test *************************************************************/

template <typename T>
void stack_push_test()
{
    ft::stack<T> stack;

    for (typename ft::stack<T>::size_type i = 0; i < 5; i++) {
        assert(stack.size() == i);
        stack.push(T());
    }
}

/****** Size test *************************************************************/

template <typename T>
void stack_size_test()
{
    // do more tests using pop() and push()
}

/****** Top test **************************************************************/

template <typename T>
void stack_top_test()
{
    // do more tests using pop() and push()
}

/****** Pop test **************************************************************/

template <typename T>
void stack_pop_test()
{
    ft::stack<T> stack(ft::vector<T>(10, T()));

    for (typename ft::stack<T>::size_type i = 0; i < 10; i++) {
        assert(stack.size() == 10 - i);
        stack.pop();
    }
}

/****** All tests *************************************************************/

int main()
{
//    allocator_test(); // TODO: first complete into output_vector.cpp

//    stack_constructor_test<int>();
//    stack_constructor_test<double>();
//    stack_constructor_test<Foo>(); // TODO: first construct vector with Foo

//    stack_empty_test<int>();
//    stack_empty_test<double>();

//    stack_push_test<int>(); // TODO: fix vector push_back() timing before

//    stack_size_test<int>(); // TODO: do pop() and push() tests before

//    stack_top_test<int>(); // TODO: do pop() and push() tests before

//    stack_pop_test<int>();

//    stack_operators_test<int>(); // TODO

    return 0;
}
