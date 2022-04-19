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
    NAMESPACE::vector<int> v;

    for (NAMESPACE::vector<int>::size_type i = 0; i < 1000000; i++)
        v.reserve(i);

    return 0;
}
