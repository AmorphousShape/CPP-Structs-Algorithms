#include "../algorithms.hpp"
#include <cassert>

using namespace std;

int main() {
    // Test Case 1: Basic case
    {
        int profits[] = {0, 60, 100, 120};
        int weights[] = {0, 10, 20, 30};
        Knapsack ks(3, 50, profits, weights);
        assert(ks.getProfit() == 220);
    }

    // Test Case 2: No items
    {
        int profits[] = {0};
        int weights[] = {0};
        Knapsack ks(0, 50, profits, weights);
        assert(ks.getProfit() == 0);
    }

    // Test Case 3: Max weight is 0
    {
        int profits[] = {0, 100, 200};
        int weights[] = {0, 1, 2};
        Knapsack ks(2, 0, profits, weights);
        assert(ks.getProfit() == 0);
    }

    // Test Case 4: All items too heavy
    {
        int profits[] = {0, 10, 20, 30};
        int weights[] = {0, 100, 200, 300};
        Knapsack ks(3, 50, profits, weights);
        assert(ks.getProfit() == 0);
    }

    // Test Case 5: Just enough capacity for one item
    {
        int profits[] = {0, 10, 20, 30};
        int weights[] = {0, 40, 50, 60};
        Knapsack ks(3, 50, profits, weights);
        assert(ks.getProfit() == 20);
    }

    // Test Case 6: Choose optimal subset
    {
        int profits[] = {0, 20, 5, 10, 40, 15, 25};
        int weights[] = {0, 1, 2, 3, 8, 7, 4};
        Knapsack ks(6, 10, profits, weights);
        assert(ks.getProfit() == 60);
    }

    return 0;
}