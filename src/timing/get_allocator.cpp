#if defined(STD) == 0 && defined(FT) == 0
#error need to #define `STD` or `FT`
#endif

#ifdef FT
#include "ft_vector.hpp"
#define NAMESPACE ft
#endif

#ifdef STD
#include <vector>
#define NAMESPACE std
#endif

int main()
{
    NAMESPACE::vector<int> v(10, 42);
    NAMESPACE::vector<int>::allocator_type alloc;

    for (int i = 0; i < 10000000; i++)
        alloc = v.get_allocator();

    (void)alloc;

    return 0;
}
