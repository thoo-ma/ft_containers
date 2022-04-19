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
    NAMESPACE::vector<int> v0(100, 21);
    NAMESPACE::vector<int> v1[10000];
    NAMESPACE::vector<int> v2[10000];

    for (int i = 0; i < 10000; i++)
        v1[i] = v0;

    for (int i = 0; i < 10000; i++)
        v2[i] = v0;

    return 0;
}
