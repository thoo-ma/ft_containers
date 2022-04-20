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

#include <chrono>
#include <iostream>
#include <fstream>
#include <cstring> // strcmp

#define xstr(s) str(s)
#define str(s) #s

using namespace std::chrono;

int main()
{
    // open file
    std::ofstream outfile ("timing.csv", std::ofstream::app);

    // check for open error
    if (outfile.rdstate())
    {
        std::cout << "Error: can't open timing.csv" << std::endl;
        return 1;
    }

    // append to file
    strcmp(xstr(NAMESPACE), "ft") == 0
    ? outfile << "vector,begin,"
    : outfile << ",";

    // data we will operate on
    NAMESPACE::vector<int> v(10, 42);
    NAMESPACE::vector<int>::iterator it;

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000000; i++)
        it = v.begin();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    duration<double> delta = end - start;

    // append delta
    outfile << delta.count();

    // close file
    outfile.close();

    // silent warnings
    (void)it;

    return 0;
}
