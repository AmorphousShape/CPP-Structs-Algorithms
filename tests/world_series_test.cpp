#include "../algorithms.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

bool checkDoubleEqual(double a, double b) {
    return (abs(a - b) < 1e-9);
}

int main() {

    // Test Case 1: All probabilities are 0.5
    {
        double probs[] = {0.5, 0.5, 0.5, 0.5, 0.5};
        vector<vector<double>> wsMatrix = worldSeries(2, probs);

        assert(wsMatrix.size() == 3);
        for (int i = 0; i < 3; i++) {
            assert(wsMatrix[i].size() == 3);
        }

        // Exact values
        assert(checkDoubleEqual(wsMatrix[0][0], 1.0));
        assert(checkDoubleEqual(wsMatrix[0][1], 0.5));
        assert(checkDoubleEqual(wsMatrix[0][2], 0.25));
        assert(checkDoubleEqual(wsMatrix[1][0], 0.5));
        assert(checkDoubleEqual(wsMatrix[1][1], 0.5));
        assert(checkDoubleEqual(wsMatrix[1][2], 0.25));
        assert(checkDoubleEqual(wsMatrix[2][0], 0.25));
        assert(checkDoubleEqual(wsMatrix[2][1], 0.25));
        assert(checkDoubleEqual(wsMatrix[2][2], 0.0));
    }

    // Test Case 2: Mixed probabilities
    {
        double probs[] = {0.6, 0.4, 0.7, 0.3, 0.5};
        vector<vector<double>> wsMatrix = worldSeries(2, probs);

        assert(wsMatrix.size() == 3);
        for (int i = 0; i < 3; i++) {
            assert(wsMatrix[i].size() == 3);
        }

        // Matrix structure holds
        assert(checkDoubleEqual(wsMatrix[0][0], 1.0));
        assert(checkDoubleEqual(wsMatrix[2][2], 0.0));

        // Relative relationships
        assert(wsMatrix[0][1] < wsMatrix[0][0]); // More games won by B → less prob for A
        assert(wsMatrix[1][0] < wsMatrix[0][0]); // More games won by A → fewer paths remaining
    }

    // Test Case 3: A always wins
    {
        double probs[] = {1.0, 1.0, 1.0, 1.0, 1.0};
        vector<vector<double>> wsMatrix = worldSeries(2, probs);

        assert(wsMatrix.size() == 3);
        for (int i = 0; i < 3; i++) {
            assert(wsMatrix[i].size() == 3);
        }

        // If A wins every match, then:
        // - Probability of A winning 2 is 1
        // - Probability of B winning anything is 0

        assert(checkDoubleEqual(wsMatrix[0][0], 1.0));
        assert(checkDoubleEqual(wsMatrix[1][0], 1.0));
        assert(checkDoubleEqual(wsMatrix[2][0], 1.0));
        assert(checkDoubleEqual(wsMatrix[0][1], 0.0));
        assert(checkDoubleEqual(wsMatrix[1][1], 0.0));
        assert(checkDoubleEqual(wsMatrix[2][1], 0.0));
        assert(checkDoubleEqual(wsMatrix[0][2], 0.0));
        assert(checkDoubleEqual(wsMatrix[1][2], 0.0));
        assert(checkDoubleEqual(wsMatrix[2][2], 0.0));
    }

    // Test Case 4: A always loses
    {
        double probs[] = {0.0, 0.0, 0.0, 0.0, 0.0};
        vector<vector<double>> wsMatrix = worldSeries(2, probs);

        assert(wsMatrix.size() == 3);
        for (int i = 0; i < 3; i++) {
            assert(wsMatrix[i].size() == 3);
        }

        // If A always loses:
        // - Probability of B winning 2 is 1
        // - Probability of A winning anything is 0

        assert(checkDoubleEqual(wsMatrix[0][0], 1.0));
        assert(checkDoubleEqual(wsMatrix[0][1], 1.0));
        assert(checkDoubleEqual(wsMatrix[0][2], 1.0));
        assert(checkDoubleEqual(wsMatrix[1][0], 0.0));
        assert(checkDoubleEqual(wsMatrix[1][1], 0.0));
        assert(checkDoubleEqual(wsMatrix[1][2], 0.0));
        assert(checkDoubleEqual(wsMatrix[2][0], 0.0));
        assert(checkDoubleEqual(wsMatrix[2][1], 0.0));
        assert(checkDoubleEqual(wsMatrix[2][2], 0.0));
    }

    return 0;
}