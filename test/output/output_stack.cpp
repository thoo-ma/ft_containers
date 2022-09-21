#include <stack>
#include <vector>
#include <cassert>

#include "ft_stack.hpp"
#include "../utils/colors.hpp" // log.hpp

/// @todo add test with custom datatype

/****** Constructor test ******************************************************/

template <typename Stack>
void stack_constructor_test()
{
    typedef typename Stack::value_type      Value;
    typedef typename Stack::container_type  Container;

    // Constructed by default
    assert(Stack().size() == 0);
    assert(Stack().empty() == true);

    // Constructed by fill
    assert(Stack(Container(10, Value())).size() == 10);
    assert(Stack(Container(10, Value())).empty() == false);

    log("constructor");
}

/****** Functions test ********************************************************/

template <typename Stack, typename Container, typename Value, typename Size>
void stack_empty_test()
{
    // underlying container constructed by default
    assert(Stack().empty() == true);

    // underlying container constructed with size 0
    assert(Stack(Container(0)).empty() == true);

    // underlying container constructed with size > 0
    assert(Stack(Container(10)).empty() == false);

    log("empty()");
}

template <typename Stack, typename Container, typename Value, typename Size>
void stack_size_test()
{
    assert(Stack().size() == 0);
    assert(Stack(Container(10)).size() == 10);

    Stack stack;

    for (Size i = 0; i < 10; i++)
    {
        assert(stack.size() == i);
        stack.push(Value(i));
    }

    for (Size i = 0; i < 10; i++)
    {
        assert(stack.size() == 10 - i);
        stack.pop();
    }

    log("size()");
}

template <typename Stack, typename Container, typename Value, typename Size>
void stack_top_test()
{
    Stack stack;

    for (Size i = 0; i < 10; i++)
    {
        stack.push(Value(i));
        assert(stack.top() == Value(i));
    }

    for (Size i = 0; i < 10; i++)
    {
        assert(stack.top() == Value(10 - i- 1));
        stack.pop();
    }

    log("top()");
}

template <typename Stack, typename Container, typename Value, typename Size>
void stack_pop_test()
{
    Stack stack(Container(10));

    for (Size i = 0; i < 10; i++)
    {
        assert(stack.size() == 10 - i);
        stack.pop();
    }

    assert(stack.empty() == true);

    /// @note If we pop again, std::stack won't remain empty whereas ft::stack will
    // stack.pop();
    // assert(stack.empty() == true);

    log("pop()");
}

template <typename Stack, typename Container, typename Value, typename Size>
void stack_push_test()
{
    Stack stack;

    for (Size i = 0; i < 21; i++)
    {
        assert(stack.size() == i);
        stack.push(Value(i));
        assert(stack.top() == Value(i));
    }

    log("push()");
}

template <typename Stack>
void stack_functions_test()
{
    typedef typename Stack::size_type       Size;
    typedef typename Stack::value_type      Value;
    typedef typename Stack::container_type  Container;

    stack_top_test<Stack, Container, Value, Size>();
    stack_pop_test<Stack, Container, Value, Size>();
    stack_size_test<Stack, Container, Value, Size>();
    stack_push_test<Stack, Container, Value, Size>();
    stack_empty_test<Stack, Container, Value, Size>();
}

/****** Operators test ********************************************************/

template <typename Stack, typename Container>
void stack_equal_test()
{
    assert(Stack() == Stack());
    assert(Stack() == Stack(Container()));
    assert(Stack(Container(10)) == Stack(Container(10)));
    assert(Stack(Container(10,21)) == Stack(Container(10,21)));

    log("operator==");
}

template <typename Stack, typename Container>
void stack_not_equal_test()
{
    // with different sizes
    assert(Stack(Container()) != Stack(Container(1)));
    assert(Stack(Container(0)) != Stack(Container(1)));
    assert(Stack(Container(1)) != Stack(Container(10)));

    // with different values
    assert(Stack(Container(4,21)) != Stack(Container(4,42)));

    log("operator!=");
}

template <typename Stack, typename Container>
void stack_less_than_test()
{
    // with different sizes
    assert(Stack(Container()) < Stack(Container(1)));
    assert(Stack(Container(0)) < Stack(Container(1)));
    assert(Stack(Container(1)) < Stack(Container(2)));

    // with different values
    assert(Stack(Container(1, 21)) < Stack(Container(1, 42)));

    log("operator<");
}

template <typename Stack, typename Container>
void stack_greater_than_test()
{
    // with different sizes
    assert(Stack(Container(1)) > Stack(Container()));
    assert(Stack(Container(1)) > Stack(Container(0)));
    assert(Stack(Container(2)) > Stack(Container(1)));

    // with different values
    assert(Stack(Container(1, 42)) > Stack(Container(1, 21)));

    log("operator>");
}

template <typename Stack, typename Container>
void stack_less_than_equal_test()
{
    // with different sizes
    assert(Stack(Container()) <= Stack(Container()));
    assert(Stack(Container()) <= Stack(Container(1)));
    assert(Stack(Container(0)) <= Stack(Container(0)));
    assert(Stack(Container(0)) <= Stack(Container(1)));
    assert(Stack(Container(1)) <= Stack(Container(1)));
    assert(Stack(Container(1)) <= Stack(Container(2)));

    // with different values
    assert(Stack(Container(1, 21)) <= Stack(Container(1, 21)));
    assert(Stack(Container(1, 21)) <= Stack(Container(1, 42)));
    assert(Stack(Container(1, 21)) <= Stack(Container(2, 21)));

    log("operator<=");
}

template <typename Stack, typename Container>
void stack_greater_than_equal_test()
{
    // with different sizes
    assert(Stack(Container()) >= Stack(Container()));
    assert(Stack(Container(1)) >= Stack(Container()));
    assert(Stack(Container(0)) >= Stack(Container(0)));
    assert(Stack(Container(1)) >= Stack(Container(0)));
    assert(Stack(Container(1)) >= Stack(Container(1)));
    assert(Stack(Container(2)) >= Stack(Container(1)));

    // with different values
    assert(Stack(Container(1, 21)) >= Stack(Container(1, 21)));
    assert(Stack(Container(1, 42)) >= Stack(Container(1, 21)));
    assert(Stack(Container(2, 21)) >= Stack(Container(1, 21)));

    log("operator>=");
}

template <typename Stack>
void stack_operators_test()
{
    typedef typename Stack::container_type Container;

    stack_equal_test<Stack, Container>();
    stack_not_equal_test<Stack, Container>();
    stack_less_than_test<Stack, Container>();
    stack_greater_than_test<Stack, Container>();
    stack_less_than_equal_test<Stack, Container>();
    stack_greater_than_equal_test<Stack, Container>();
}

/****** Stack test ************************************************************/

template <typename T>
void stack_test()
{
    // implicit underlying container
    stack_constructor_test<std::stack<T>>();
    stack_constructor_test< ft::stack<T>>();

    // explicit underlying container
    stack_constructor_test<std::stack<std::vector<T>>>();
    stack_constructor_test< ft::stack<std::vector<T>>>();

    stack_functions_test<std::stack<T>>();
    stack_functions_test< ft::stack<T>>();

    stack_operators_test<std::stack<T>>();
    stack_operators_test< ft::stack<T>>();
}

/****** All tests *************************************************************/

int main()
{
    stack_test<int>();
    stack_test<double>();
    //stack_test<A>();
    return 0;
}
