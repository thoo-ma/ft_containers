#include <stack>
#include <deque>
#include <vector>
#include <cassert>
#include <iostream>
#include <stdexcept>

#include "ft_stack.hpp"
#include "ft_vector.hpp"

#include "../utils/colors.hpp"

#include <typeinfo> // typeid

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

    std::cout << "constructor " << GREEN << "OK" << RESET << std::endl;
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

    std::cout << "empty " << GREEN << "OK" << RESET << std::endl;
}

/****** Push test *************************************************************/

template <typename T>
void stack_push_test()
{
    ft::stack<T> stack;

    for (typename ft::stack<T>::size_type i = 0; i < 21; i++) {
        assert(stack.size() == i);
        stack.push(T());
    }

    std::cout << "push " << GREEN << "OK" << RESET << std::endl;
}

/****** Size test *************************************************************/

template <typename T>
void stack_size_test()
{
    assert(ft::stack<T>().size() == 0);

    assert(ft::stack<T>(ft::vector<T>(10)).size() == 10);

    ft::stack<T> stack;

    for (typename ft::stack<T>::size_type i = 0; i < 10; i++) {
        assert(stack.size() == i);
        stack.push(static_cast<int>(i));
    }

    for (typename ft::stack<T>::size_type i = 0; i < 10; i++) {
        assert(stack.size() == 10 - i);
        stack.pop();
    }

    std::cout << "size " << GREEN << "OK" << RESET << std::endl;
}

/****** Top test **************************************************************/

template <typename T>
void stack_top_test()
{
    ft::stack<T> stack;

    for (typename ft::stack<T>::size_type i = 0; i < 10; i++) {
        stack.push(static_cast<T>(i));
        assert(stack.top() == static_cast<T>(i));
    }

    for (typename ft::stack<T>::size_type i = 0; i < 10; i++) {
        assert(stack.top() == static_cast<T>(10 - i- 1));
        stack.pop();
    }

    std::cout << "top " << GREEN << "OK" << RESET << std::endl;
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

    std::cout << "pop " << GREEN << "OK" << RESET << std::endl;
}

/****** Operators *************************************************************/

template <typename T>
void stack_equal_test()
{
    // empty stack
    assert(ft::stack<T>() == ft::stack<T>());
    assert(ft::stack<T>() == ft::stack<T>(0));
    assert(ft::stack<T>() == ft::stack<T>(ft::vector<T>()));

    // non-empty with default values
    {
        ft::vector<T> v(10);
        assert(ft::stack<T>(v) == ft::stack<T>(v));
    }

    // non-empty with specified values
    {
        ft::vector<T> v(10, 21);
        assert(ft::stack<T>(v) == ft::stack<T>(v));
    }

    std::cout << "operator== " << GREEN << "OK" << RESET << std::endl;
}

template <typename T>
void stack_not_equal_test()
{
    assert(ft::stack<T>(ft::vector<T>()) != ft::stack<T>(ft::vector<T>(1)));
    assert(ft::stack<T>(ft::vector<T>(0)) != ft::stack<T>(ft::vector<T>(1)));
    assert(ft::stack<T>(ft::vector<T>(1)) != ft::stack<T>(ft::vector<T>(10)));
    assert(ft::stack<T>(ft::vector<T>(4,21)) != ft::stack<T>(ft::vector<T>(4,42)));
    std::cout << "operator!= " << GREEN << "OK" << RESET << std::endl;
}

template <typename T>
void stack_less_than_test()
{
    {
        // with different sizes
        assert(ft::stack<T>(ft::vector<T>()) < ft::stack<T>(ft::vector<T>(1)));
        assert(ft::stack<T>(ft::vector<T>(0)) < ft::stack<T>(ft::vector<T>(1)));
        assert(ft::stack<T>(ft::vector<T>(1)) < ft::stack<T>(ft::vector<T>(2)));

        // with different values
        assert(ft::stack<T>(ft::vector<T>(1, 21)) < ft::stack<T>(ft::vector<T>(1, 42)));
    }
    std::cout << "operator< " << GREEN << "OK" << RESET << std::endl;
}

template <typename T>
void stack_greater_than_test()
{
    // with different sizes
    assert(ft::stack<T>(ft::vector<T>(1)) > ft::stack<T>(ft::vector<T>()));
    assert(ft::stack<T>(ft::vector<T>(1)) > ft::stack<T>(ft::vector<T>(0)));
    assert(ft::stack<T>(ft::vector<T>(2)) > ft::stack<T>(ft::vector<T>(1)));

    // with different values
    assert(ft::stack<T>(ft::vector<T>(1, 42)) > ft::stack<T>(ft::vector<T>(1, 21)));

    std::cout << "operator> " << GREEN << "OK" << RESET << std::endl;
}

template <typename T>
void stack_less_than_equal_test()
{
    // with different sizes
    assert(ft::stack<T>(ft::vector<T>()) <= ft::stack<T>(ft::vector<T>()));
    assert(ft::stack<T>(ft::vector<T>()) <= ft::stack<T>(ft::vector<T>(1)));
    assert(ft::stack<T>(ft::vector<T>(0)) <= ft::stack<T>(ft::vector<T>(0)));
    assert(ft::stack<T>(ft::vector<T>(0)) <= ft::stack<T>(ft::vector<T>(1)));
    assert(ft::stack<T>(ft::vector<T>(1)) <= ft::stack<T>(ft::vector<T>(1)));
    assert(ft::stack<T>(ft::vector<T>(1)) <= ft::stack<T>(ft::vector<T>(2)));

    // with different values
    assert(ft::stack<T>(ft::vector<T>(1, 21)) <= ft::stack<T>(ft::vector<T>(1, 21)));
    assert(ft::stack<T>(ft::vector<T>(1, 21)) <= ft::stack<T>(ft::vector<T>(1, 42)));
    assert(ft::stack<T>(ft::vector<T>(1, 21)) <= ft::stack<T>(ft::vector<T>(2, 21)));

    std::cout << "operator<= " << GREEN << "OK" << RESET << std::endl;
}

template <typename T>
void stack_greater_than_equal_test()
{
    // with different sizes
    assert(ft::stack<T>(ft::vector<T>()) >= ft::stack<T>(ft::vector<T>()));
    assert(ft::stack<T>(ft::vector<T>(1)) >= ft::stack<T>(ft::vector<T>()));
    assert(ft::stack<T>(ft::vector<T>(0)) >= ft::stack<T>(ft::vector<T>(0)));
    assert(ft::stack<T>(ft::vector<T>(1)) >= ft::stack<T>(ft::vector<T>(0)));
    assert(ft::stack<T>(ft::vector<T>(1)) >= ft::stack<T>(ft::vector<T>(1)));
    assert(ft::stack<T>(ft::vector<T>(2)) >= ft::stack<T>(ft::vector<T>(1)));

    // with different values
    assert(ft::stack<T>(ft::vector<T>(1, 21)) >= ft::stack<T>(ft::vector<T>(1, 21)));
    assert(ft::stack<T>(ft::vector<T>(1, 42)) >= ft::stack<T>(ft::vector<T>(1, 21)));
    assert(ft::stack<T>(ft::vector<T>(2, 21)) >= ft::stack<T>(ft::vector<T>(1, 21)));

    std::cout << "operator>= " << GREEN << "OK" << RESET << std::endl;
}

template <typename T>
void stack_operators_test()
{
    stack_equal_test<T>();
    stack_not_equal_test<T>();
    stack_less_than_test<T>();
    stack_greater_than_test<T>();
    stack_less_than_equal_test<T>();
    stack_greater_than_equal_test<T>();
}

/****** All tests *************************************************************/

int main()
{
    stack_constructor_test<int>();
//    stack_constructor_test<double>();
//    stack_constructor_test<std::vector<int>>();

    stack_empty_test<int>();
//    stack_empty_test<double>();
    stack_push_test<int>();
    stack_size_test<int>();
    stack_top_test<int>();
    stack_pop_test<int>();

    stack_operators_test<int>();

    return 0;
}
