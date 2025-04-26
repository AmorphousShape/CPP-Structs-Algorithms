#include "../algorithms.hpp"

#include <iostream>
#include <sstream>
#include <cassert>

int main() {
    Fib *fib = new Fib();

    __uint128_t num;
    ostringstream out;
    
    fib->print(100, out);

    string result = out.str();
    assert(result == "fib(100) = 354224848179261915075\n");

    // The 100th being correct implies that all previous numbers are correct
    return 0;
}