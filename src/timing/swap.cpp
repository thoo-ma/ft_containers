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
    NAMESPACE::vector<int> v1(1000, 42);
    NAMESPACE::vector<int> v2(1000, 21);

    for (int i = 0; i < 1000000; i++)
        v1.swap(v2);

    return 0;
}
