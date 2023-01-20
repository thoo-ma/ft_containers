#include <stack>
#include <vector>

#include "ft_stack.hpp"
#include "utils.hpp"

/****** Constructor test ******************************************************/

template <typename Stack>
void stack_constructor_test()
{
    typedef typename Stack::value_type      Value;
    typedef typename Stack::container_type  Container;

    // Constructed by default
    expect(Stack().size() == 0);
    expect(Stack().empty() == true);

    // Constructed by fill
    expect(Stack(Container(10, Value())).size() == 10);
    expect(Stack(Container(10, Value())).empty() == false);

    log("constructor");
}

/****** Functions test ********************************************************/

template <typename Stack, typename Container, typename Value, typename Size>
void stack_empty_test()
{
    // underlying container constructed by default
    expect(Stack().empty() == true);

    // underlying container constructed with size 0
    expect(Stack(Container(0)).empty() == true);

    // underlying container constructed with size > 0
    expect(Stack(Container(10)).empty() == false);

    log("empty()");
}

template <typename Stack, typename Container, typename Value, typename Size>
void stack_size_test()
{
    expect(Stack().size() == 0);
    expect(Stack(Container(10)).size() == 10);

    Stack stack;

    for (int i = 0; i < 10; i++)
    {
        expect(stack.size() == static_cast<Size>(i));
        stack.push(Value(i));
    }

    for (Size i = 0; i < 10; i++)
    {
        expect(stack.size() == 10 - i);
        stack.pop();
    }

    log("size()");
}

template <typename Stack, typename Container, typename Value, typename Size>
void stack_top_test()
{
    Stack stack;

    for (int i = 0; i < 10; i++)
    {
        Value val = Value(i);
        stack.push(val);
        expect(stack.top() == val);
    }

    for (int i = 0; i < 10; i++)
    {
        expect(stack.top() == Value(10 - i- 1));
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
        expect(stack.size() == 10 - i);
        stack.pop();
    }

    expect(stack.empty() == true);

    /// @note If we pop again, std::stack won't remain empty whereas ft::stack will
    // stack.pop();
    // expect(stack.empty() == true);

    log("pop()");
}

template <typename Stack, typename Container, typename Value, typename Size>
void stack_push_test()
{
    Stack stack;

    for (int i = 0; i < 21; i++)
    {
        Value val(i);
        expect(stack.size() == static_cast<Size>(i));
        stack.push(val);
        expect(stack.top() == val);
    }

    log("push()");
}

template <typename Stack>
void stack_functions_test()
{
    typedef typename Stack::size_type       Size;
    typedef typename Stack::value_type      Value;
    typedef typename Stack::container_type  Container;

    stack_top_test  <Stack, Container, Value, Size>();
    stack_pop_test  <Stack, Container, Value, Size>();
    stack_size_test <Stack, Container, Value, Size>();
    stack_push_test <Stack, Container, Value, Size>();
    stack_empty_test<Stack, Container, Value, Size>();
}

/****** Operators test ********************************************************/

template <typename Stack, typename Container>
void stack_equal_test()
{
    expect(Stack() == Stack());
    expect(Stack() == Stack(Container()));
    expect(Stack(Container(10)) == Stack(Container(10)));
    expect(Stack(Container(10,21)) == Stack(Container(10,21)));

    log("operator==");
}

template <typename Stack, typename Container>
void stack_not_equal_test()
{
    // with different sizes
    expect(Stack(Container()) != Stack(Container(1)));
    expect(Stack(Container(0)) != Stack(Container(1)));
    expect(Stack(Container(1)) != Stack(Container(10)));

    // with different values
    expect(Stack(Container(4,21)) != Stack(Container(4,42)));

    log("operator!=");
}

template <typename Stack, typename Container>
void stack_less_than_test()
{
    // with different sizes
    expect(Stack(Container()) < Stack(Container(1)));
    expect(Stack(Container(0)) < Stack(Container(1)));
    expect(Stack(Container(1)) < Stack(Container(2)));

    // with different values
    expect(Stack(Container(1, 21)) < Stack(Container(1, 42)));

    log("operator<");
}

template <typename Stack, typename Container>
void stack_greater_than_test()
{
    // with different sizes
    expect(Stack(Container(1)) > Stack(Container()));
    expect(Stack(Container(1)) > Stack(Container(0)));
    expect(Stack(Container(2)) > Stack(Container(1)));

    // with different values
    expect(Stack(Container(1, 42)) > Stack(Container(1, 21)));

    log("operator>");
}

template <typename Stack, typename Container>
void stack_less_than_equal_test()
{
    // with different sizes
    expect(Stack(Container()) <= Stack(Container()));
    expect(Stack(Container()) <= Stack(Container(1)));
    expect(Stack(Container(0)) <= Stack(Container(0)));
    expect(Stack(Container(0)) <= Stack(Container(1)));
    expect(Stack(Container(1)) <= Stack(Container(1)));
    expect(Stack(Container(1)) <= Stack(Container(2)));

    // with different values
    expect(Stack(Container(1, 21)) <= Stack(Container(1, 21)));
    expect(Stack(Container(1, 21)) <= Stack(Container(1, 42)));
    expect(Stack(Container(1, 21)) <= Stack(Container(2, 21)));

    log("operator<=");
}

template <typename Stack, typename Container>
void stack_greater_than_equal_test()
{
    // with different sizes
    expect(Stack(Container()) >= Stack(Container()));
    expect(Stack(Container(1)) >= Stack(Container()));
    expect(Stack(Container(0)) >= Stack(Container(0)));
    expect(Stack(Container(1)) >= Stack(Container(0)));
    expect(Stack(Container(1)) >= Stack(Container(1)));
    expect(Stack(Container(2)) >= Stack(Container(1)));

    // with different values
    expect(Stack(Container(1, 21)) >= Stack(Container(1, 21)));
    expect(Stack(Container(1, 42)) >= Stack(Container(1, 21)));
    expect(Stack(Container(2, 21)) >= Stack(Container(1, 21)));

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
    stack_constructor_test< ft::stack< ft::vector<T>>>();

    stack_functions_test<std::stack<T>>();
    stack_functions_test< ft::stack<T>>();

    stack_operators_test<std::stack<T>>();
    stack_operators_test< ft::stack<T>>();
}

/****** All tests *************************************************************/

int main()
{
    stack_test<A>();
    stack_test<int>();
    return 0;
}