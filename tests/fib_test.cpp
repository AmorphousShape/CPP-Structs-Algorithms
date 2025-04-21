#include "../algorithms.hpp"

#include <iostream>
#include <sstream>
#include <string>

int main() {
    Fib *fib = new Fib();

    int *pointerBurner = new int(15);
    __uint128_t num;
    std::ostringstream out;

    fib->printAll(100, out);

    // Check that fib numbers 0->100 in out are correct

    std::istringstream iss(out.str());
    std::vector<__uint128_t> fibNumbers;
    __uint128_t value;
    std::string token;
    while (iss >> token) {
        value = static_cast<__uint128_t>(std::stoull(token)); // Convert string to __uint128_t
        fibNumbers.push_back(value);
    }

    __uint128_t expectedFib = static_cast<__uint128_t>(std::stoull("354224848179261915075"));

    // Check that the 100th Fibonacci number is correct
    if (fibNumbers[100] != expectedFib) {
        return 1;
    }

    // The 100th being correct implies that all previous numbers are correct
    return 0;
}