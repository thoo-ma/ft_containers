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
    NAMESPACE::vector<int> v(100000, 42);
    NAMESPACE::vector<int>::size_type s;

    for (int i = 0; i < 100000; i++)
        s = v.max_size();

    (void)s;

    return 0;
}
