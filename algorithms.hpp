/**
 * @file algorithms.h
 * 
 * @brief Header file including several algorithms
 * 
 * @details This file includes the following algorithms:
 * * - All-Pairs Shortest Path (APSP)
 * * - Fibonacci Heap
 * * - 0-1 Knapsack
 * * - Longest Common Subsequence (LCS)
 * * - Matrix Chain Multiplication
 * * - World Series Probability Matrix
 */

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <vector>
#include <climits>
#include <ctime>

using namespace std;

/**
 * @brief All-Pairs Shortest Path (APSP) class
 * 
 * @details This class implements the Floyd-Warshall algorithm to find the shortest paths
 *         between all pairs of vertices in a directed, weighted graph. Negative vertex
 *         cycles will be detected and will throw runtime errors.
 */
class APSP {

    /**
     * @brief Adjacency matrix representing the graph
     * 
     * @details From row to col; int_max if no edge
     */
    vector< vector<int> > adjacency;

    /**
     * @brief Number of vertices in the graph
     */
    int n;

    /**
     * @brief Indicates whether the APSP table has been built
     */
    bool built;

    /**
     * @brief Build the APSP table using the Floyd-Warshall algorithm
     */
    void build() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (adjacency[j][i] == INT_MAX || adjacency[i][k] == INT_MAX) {
                        continue;
                    }
                    if (adjacency[j][i] + adjacency[i][k] < adjacency[j][k]) {
                        adjacency[j][k] = adjacency[j][i] + adjacency[i][k];
                    }
                }
            }
        }

        // After table is built, check for negative cycles and set built to true
        checkNegativeCycle();
        built = true;
    }

    /**
     * @brief Checks for negative cycles in the graph, throw error if found
     */
    void checkNegativeCycle() {
        for (int i = 0; i < n; i++) {
            if (adjacency[i][i] < 0) {
                throw runtime_error("Negative cycle detected at vertex " + to_string(i) + "\n");
            }
        }
    }

    public:

    /**
     * @brief Constructor for the APSP class
     * 
     * @details Initializes the adjacency matrix for n vertices.
     * 
     * @param n Number of vertices in the graph
     */
    APSP(int n) {
        this->n = n;
        built = false;
        for (int i = 0; i < n; i++) {
            vector<int> row;
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    row.push_back(0);
                    continue;
                }
                row.push_back(INT_MAX);
            }
            adjacency.push_back(row);
        }
    }

    /**
     * @brief Adds an edge to the graph
     * 
     * @param i The starting vertex (0-indexed)
     * @param j The ending vertex (0-indexed)
     * @param cost The cost of the edge from vertex i to vertex j
     */
    void addEdge(int i, int j, int cost) {
        adjacency[i][j] = cost;
        built = false;
    }

    /**
     * @brief Gets the cost of the edge from vertex i to vertex j
     * 
     * @param i The starting vertex (0-indexed)
     * @param j The ending vertex (0-indexed)
     */
    int getCost(int i, int j) {
        if (!built) {
            build();
        }

        return adjacency[i][j];
    }

    /**
     * @brief Prints the adjacency matrix of the graph
     * 
     * @param out Output stream to print to (default is cout)
     */
    void printAdjacency(ostream &out = cout) {
        if (!built) {
            build();
        }

        for (int i = 0; i < n; i++) {
            cout << i + 1 << ": ";
            for (int j = 0; j < n; j++) {
                if (adjacency[i][j] == INT_MAX) {
                    cout << "inf ";
                    continue;
                }
                cout << adjacency[i][j] << " ";
            }
            cout << endl;
        }
    }
};

/**
 * @brief Calculates fibonacci numbers using a recursive, dynamic programming approach
 */
class Fib {

    __uint128_t fibList[186];

    /**
     * @brief Recursive function to calculate the nth Fibonacci number
     * 
     * @param n Pointer to the integer value of n for which to calculate the Fibonacci number
     */
    __uint128_t fib(int *n) {

        // Check if number is too large for __uint128_t
        if (*n > 185) {
            throw runtime_error("Fibonacci number too large for unsigned 128-bit int\n");
        }

        // Check if number is stored
        if (fibList[*n] != 0) {
            return fibList[*n];
        }

        // If number is not stored, calculate it
        int a = *n - 1;
        int b = *n - 2;
        fibList[*n] = fib(&a) + fib(&b);

        return fibList[*n];
    }

    public:
        
    /**
     * @brief Constructor to initialize the Fibonacci class
     * 
     * Initializes the first two Fibonacci numbers and clears the rest of the array
     */
    Fib() {
        // Set first two fibonacci numbers and clear all other data in map
        fibList[0] = 1;
        fibList[1] = 1;
        for (int i = 2; i < 186; i++) {
            fibList[i] = 0;
        }
    }

    /**
     * @brief Print the Fibonacci number for a given n
     * 
     * @param n The integer value for which to calculate and print the Fibonacci number
     */
    void print(int n, ostream &out = cout) {
        // Unsigned 128-bit int is too large to print, so split it into two unsigned 64-bit ints for output
        __uint64_t a, b;

        __uint128_t f = fib(&n);

        // Split __uint128_t into two __uint64_t variables
        a = (__uint64_t)(f >> 64);
        b = (__uint64_t)f;

        out << "fib(" << n << ") = ";

        // Print most significant 64 bits if there are any
        if (a != 0) {
            out << a;
        }
        // Print least significant 64 bits
        out << b << endl;
    }

    /**
     * @brief Print all Fibonacci numbers from 0 to n
     * 
     * @param n Max number to print Fibonacci numbers for (inclusive) (max 185)
     */
    void printAll(int n, ostream &out = cout) {

        if (n > 185) {
            throw runtime_error("Cannot print Fibonacci numbers greater than 185 with unsigned 128-bit int\n");
        }

        // Print all fibonacci numbers up to n (inclusive)
        for (int i = 0; i < n; i++) {
            print(i, out);
        }
    }
};

/**
 * @brief Stores information for and solves the 0-1 knapsack problem using dynamic programming
 */
class Knapsack {

    /**
     * @brief Number of items in the knapsack
     */
    int n;

    /**
     * @brief Maximum weight of the knapsack
     */
    int max;
    
    /**
     * @brief Array of weights for each item
     */
    int *weights;
    
    /**
     * @brief Array of profits for each item
     */
    int *profits;

    /**
     * @brief Indicates whether the table has been built or not
     */
    bool built;

    /**
     * @brief Array of booleans indicating whether an object was chosen or not
     */
    bool *objects;

    /**
     * @brief Dynamic programming table for the knapsack problem
     */
    vector< vector<int> > table;

    /**
     * @brief Build the dynamic programming table for the knapsack problem
     */
    void build() {
        
        // Table building loop
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= max; k++) {
                if (j == 0) {
                    table[j][k] = 0;
                } else if (k < weights[j]) {
                    table[j][k] = table[j - 1][k];
                } else {
                    // max() function is not functioning properly, so I manually find the max
                    int 
                        a = table[j - 1][k],
                        b = table[j - 1][k - weights[j]] + profits[j];
                    if (a > b) {
                        table[j][k] = a;
                    } else {
                        table[j][k] = b;
                    }
                }
            }
        }

        // After table is built, choose the objects and set built to true
        choose();
        built = true;
    }

    /**
     * @brief Choose the objects to include in the knapsack based on the built table
     */
    void choose() {

        // Start at the bottom right corner of the table and work backwards
        int k = max;
        for (int i = n; i > 0; i--) {
            if (table[i-1][k] == table[i][k]) {
                objects[i] = false;
            } else {
                objects[i] = true;
                k -= weights[i];
            }
        }
    }

    public:

    /**
     * @brief Constructor 
     * 
     * NOTE: p and w MUST be 1-indexed
     * 
     * @param n Number of items in the knapsack
     * @param max Maximum weight of the knapsack
     * @param p Array of profits for each item (1-indexed)
     * @param w Array of weights for each item (1-indexed)
     */
    Knapsack(int n, int max, int *p, int *w) {

        this->n = n;
        this->max = max;
        built = false;
        objects = new bool[n+1];
        weights = w;
        profits = p;

        for (int i = 0; i <= n; i++) {
            vector<int> temp;
            for (int j = 0; j <= max; j++) {
                temp.push_back(0);
            }
            table.push_back(temp);
        }
    }

    /**
     * @brief Print the dynamic programming table for the knapsack problem
     */
    void printTable() {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= max; j++) {
                cout << table[i][j] << " ";
            }
            cout << endl;
        }
    }

    /**
     * @brief Print the profits, weights, and objects chosen for the knapsack problem
     */
    void printPWO() {
        if (!built) {
            build();
        }
        cout << "Profit: ";
        for (int i = 1; i <= n; i++) {
            cout << profits[i] << " ";
        }
        cout << endl;
        cout << "Weight: ";
        for (int i = 1; i <= n; i++) {
            cout << weights[i] << " ";
        }
        cout << endl;
        cout << "Objects Chosen: ";
        for (int i = 1; i <= n; i++) {
            cout << objects[i] << " ";
        }
    }

    /**
     * @brief Get the maximum profit of the knapsack problem
     */
    int getProfit() {
        if (!built) {
            build();
        }
        return table[n][max];
    }

};

/**
 * @class LCS
 * 
 * @brief Finds the longest common subsequence (LCS) of two strings
 * 
 * Functions requiring the LCS will calculate it before returning.
 */
class LCS {

    private:

        /**
         * @brief First string to find the LCS of
         */
        string s1;
        
        /**
         * @brief Second string to find the LCS of
         */
        string s2;
        
        /**
         * @brief Storage for the found LCS
         */
        string foundLCS;

        /**
         * @brief Matrix to store LCS lengths
         */
        vector< vector<int> > L;

        /**
         * @brief Indicates whether LCS has been built or not
         */
        bool built;

        /**
         * @brief Recursive function to build LCS
         * 
         * @param j Current index in s1
         * @param k Current index in s2
         * 
         * @return The longest common subsequence built from the two strings
         */
        string build(int j, int k) {

            // Base Cases
            if (j == 0 || k == 0) {
                return "";
            }
            
            // If the characters are the same, add it to the LCS
            if (s1[j-1] == s2[k-1]) {
                return build(j - 1, k - 1) + s1[j-1];
            }
            
            // If the characters are different, backtrack
            if (L[j][k-1] == L[j][k]) {
                return build(j, k - 1);
            }
            return build(j - 1, k);
        }

    public:

        /**
         * @brief Constructor to initialize the LCS object
         * 
         * @param a First string for which to find the LCS
         * @param b Second string for which to find the LCS
         */
        LCS(string a, string b) {
            s1 = a;
            s2 = b;
            built = false;
        }
        
        /**
         * @brief Destructor for the LCS object
         * 
         * Nothing special, but destructor should be declared even if empty
         */
        ~LCS() {
        }

        /**
         * @brief Retrieve the longest common subsequence of the two strings
         * 
         * @return The longest common subsequence of the two strings
         */
        string get() {

            if (built) {
                return foundLCS;
            }

            // Populate vector with 0s
            for (int i = 0; i <= s1.length(); i++) {
                vector<int> temp;
                for (int j = 0; j <= s2.length(); j++) {
                    temp.push_back(0);
                }
                L.push_back(temp);
            }

            // LCS Algorithm
            for (int j = 1; j <= s1.length(); j++) {
                for (int k = 1; k <= s2.length(); k++) {
                    if (s1[j-1] == s2[k-1]) {
                        L[j][k] = L[j-1][k-1] + 1;
                    } else {
                        L[j][k] = max(L[j-1][k], L[j][k-1]);
                    }
                }
            }

            // Set foundLCS for future use and update built
            foundLCS = build(s1.length(), s2.length());
            built = true;

            return foundLCS;
        }

        /**
         * @brief Get the length of the longest common subsequence
         */
        int lcsLength() {
            if (!built) {
                get();
            }
            return foundLCS.length() - 1;
        }

        /**
         * @brief Print the matrix used to find the LCS
         */
        void printMatrix() {

            // Ensure LCS is built before printing the matrix
            if (!built) {
                get();
            }

            cout << "Matrix L: " << endl;
            for (int i = 0; i <= s1.length(); i++) {
                for (int j = 0; j <= s2.length(); j++) {
                    cout << L[i][j] << " ";
                }
                cout << endl;
            }
        }

        /**
         * @brief Update the strings for which to find the LCS
         * 
         * @param a New first string for which to find the LCS
         * @param b New second string for which to find the LCS
         */
        void newStrings(string a, string b) {
            s1 = a;
            s2 = b;
            built = false;
            L.clear();
        }
};

/**
 * @class Matrix
 * 
 * @brief Represents a matrix
 * 
 */
class Matrix {
    public:

    /**
     * @brief Number of rows in the matrix
     */
    int row;

    /**
     * @brief Number of columns in the matrix
     */
    int col;

    /**
     * @brief Data of the matrix
     */
    vector< vector<int> > data;

    /**
     * @brief Default constructor
     */
    Matrix(vector< vector<int> > m): data(m) {};

    /**
     * @brief Constructor with dimensions; initializes the matrix with 0s
     */
    Matrix(int rows, int cols) {
        row = rows;
        col = cols;
        for (int i = 0; i < rows; i++) {
            vector<int> temp;
            for (int j = 0; j < cols; j++) {
                temp.push_back(0);
            }
            data.push_back(temp);
        }
    }

    /**
     * @brief Clears the matrix data
     */
    void clear() {
        row = -1;
        col = -1;
        data.clear();
    }

    /**
     * @brief Prints the matrix
     * 
     * @param out Output stream to print to (default is cout)
     */
    void print(ostream &out = cout) {
        for (int i = 0; i < col; i++) {
            for (int j = 0; j < row; j++) {
                out << data[i][j] << " ";
            }
            out << endl;
        }
    }
};

/**
 * @class MatrixChain
 * 
 * @brief Represents a chain of matrices
 * 
 * @details Given a chain of matrices, this class finds the optimal parenthesization of the matrices and returns the product
 * 
 */
class MatrixChain {

    /**
     * @brief Number of matrices in the chain
     */
    int n;

    /**
     * @brief Whether the costs have been calculated
     */
    bool calculated;

    /**
     * @brief Solution matrix
     */
    Matrix *solution;

    /**
     * @brief Stores optimal split points
     */
    Matrix *bestK;

    /**
     * @brief Stores costs of multiplying the matrices
     */
    Matrix *cost;

    /**
     * @brief Dimensions of the matrices
     */
    vector<int> dim;

    /**
     * @brief Data of the matrices
     */
    vector<Matrix*> data;

    /**
     * @brief Calculate the costs of multiplying the matrices
     */
    void calcCosts() {
        for (int L = 1; L < n; L++) {
            for (int i = 0; i < n - L; i++) {
                int j = i + L;
                cost->data[i][j] = INT_MAX;
                for (int k = i; k < j; k++) {
                    int q = cost->data[i][k] + cost->data[k + 1][j] + dim[i] * dim[k + 1] * dim[j + 1];
                    if (q < cost->data[i][j]) {
                        cost->data[i][j] = q;
                        bestK->data[i][j] = k;
                    }
                }
            }
        }
    }
    
    /**
     * @brief Multiply two matrices
     */
    Matrix *matrixMult(Matrix *a, Matrix *b) {
        Matrix *c = new Matrix(a->row, b->col);
        for (int i = 0; i < a->row; i++) {
            for (int j = 0; j < b->col; j++) {
                for (int k = 0; k < a->col; k++) {
                    c->data[i][j] += a->data[i][k] * b->data[k][j];
                }
            }
        }
        return c;
    }

    /**
     * @brief Find the optimal parenthesization of the matrices
     * 
     * @param i Start index
     * @param j End index
     * 
     * @return Product of the matrices
     */
    Matrix *chainProduct(int i, int j) {
        if (i == j) {
            return data[i];
        }
        int k = bestK->data[i][j];
        Matrix *a = chainProduct(i, k);
        Matrix *b = chainProduct(k + 1, j);
        return matrixMult(a, b);
    }

    public:

    /**
     * @brief Copy constructor (deep copy)
     */
    MatrixChain(vector<Matrix*> m) {
        n = m.size();
        calculated = false;
        solution = new Matrix(n, n);
        bestK = new Matrix(n, n);
        cost = new Matrix(n, n);

        for (int i = 0; i < n; i++) {
            data.push_back(m[i]);
        }

        for (int i = 0; i < n; i++) {
            dim.push_back(m[i]->row);
            if (i == 0) {
                continue;
            }
            if (m[i]->row != m[i-1]->col) {
                throw runtime_error("Matrix dimensions do not match in MatrixChain constructor");
                return;
            }
        }
    }

    /**
     * @brief Add a matrix to the chain
     */
    void addMatrix(Matrix *m) {
        if (m->row != data[n - 1]->col) {
            throw runtime_error("Matrix dimensions do not match in MatrixChain::addMatrix");
            return;
        }

        data.push_back(m);
        if (calculated) {
            calculated = false;
            delete solution;
        }
        n++;
    }

    /**
     * @brief Multiply the matrices and return the product
     */
    Matrix *solve() {
        if (!calculated) {
            calcCosts();
            solution = chainProduct(0, n - 1);
        }
        return solution;
    }

};

/**
 * @brief Generates and prints the probability matrix for the world series
 * 
 * @param n number of games in the series
 * @param aProb array of probabilities for team A to win each game
 */
void worldSeries(int n, double *aProb) {

    // Create matrix
    double x[n+1][n+1];
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {

            // Base cases
            if (i == 0 && j == 0) {
                x[0][0] = 1;
            } else if (i == n && j == n) {
                x[n][n] = 0;

            // Fill in matrix
            } else if ((i != 0 && j == 0) || (i == n && j != n)) {
                x[i][j] = x[i - 1][j] * aProb[i + j];
            } else if ((i == 0 && j != 0) || (i != n && j == n)) {
                x[i][j] = x[i][j - 1] * (1 - aProb[i + j]);
            } else {
                x[i][j] = x[i - 1][j] * aProb[i + j] + x[i][j - 1] * (1 - aProb[i + j]);
            }
        }
    }

    // Print matrix
    for (int i = 0 ; i < (n+1)*(n+1); i++) {
        cout << x[i/(n+1)][i%(n+1)] << " ";
        if (i % (n+1) == n) {
            cout << endl;
        }
    }

}

#endif