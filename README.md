# C++ Data Structures and Algorithms Library

[![Algorithms](https://github.com/AmorphousShape/CPP-Structs-Algorithms/actions/workflows/algorithms_test.yml/badge.svg)](https://github.com/AmorphousShape/CPP-Structs-Algorithms/actions/workflows/algorithms_test.yml) [![Data Structs](https://github.com/AmorphousShape/CPP-Structs-Algorithms/actions/workflows/datastructs_test.yml/badge.svg)](https://github.com/AmorphousShape/CPP-Structs-Algorithms/actions/workflows/datastructs_test.yml)

This repository contains two header files, `datastructs.hpp` and `algorithms.hpp`, which implement a variety of data structures and algorithms in C++. These files are designed to be modular and reusable for various computational tasks.

---

## Table of Contents

1. [Overview](#overview)
2. [Header Files](#header-files)
   - [datastructs.h](#datastructsh)
   - [algorithms.h](#algorithmsh)
3. [Usage](#usage)
4. [Examples](#examples)

---

## Overview

This library provides implementations of advanced data structures and algorithms. It is designed for educational purposes, competitive programming, and general use in C++ projects.

Detailed documentation is available [here](https://amorphousshape.github.io/CPP-Structs-Algorithms/)

---

## Header Files

### datastructs.h

This file contains implementations of the following data structures:

1. **Circular Dynamic Array**  
   - A resizable array that supports efficient addition and deletion of elements at both ends.
   - Key features:
     - Dynamic resizing.
     - Amortized O(1) operations for adding/removing elements.
     - Supports sorting, searching, and selection operations.

2. **Heap**  
   - A minimum heap implemented using the Circular Dynamic Array.
   - Key features:
     - Efficient insertion and extraction of the minimum element.
     - O(log n) operations for insertion and extraction.

3. **Red-Black Tree**  
   - A self-balancing binary search tree.
   - Key features:
     - O(log n) operations for insertion, deletion, and search.
     - Supports rank and select operations.

---

### algorithms.h

This file contains implementations of the following algorithms:

1. **All-Pairs Shortest Path (APSP)**  
   - Implements the Floyd-Warshall algorithm to find the shortest paths between all pairs of vertices in a graph.

2. **Fibonacci Numbers**  
   - Calculates Fibonacci numbers using a recursive, dynamic programming approach.
   - Supports numbers up to the 185th Fibonacci number using custom, printable 128-bit integers.

3. **0-1 Knapsack Problem**  
   - Solves the 0-1 knapsack problem using dynamic programming.
   - Provides the maximum profit and the selected items.

4. **Longest Common Subsequence (LCS)**  
   - Finds the longest common subsequence of two strings.
   - Provides the LCS and its length.

5. **Matrix Chain Multiplication**  
   - Finds the optimal parenthesization of a chain of matrices to minimize multiplication cost.
   - Returns the resulting matrix product.

6. **World Series Probability Matrix**  
   - Generates a probability matrix for a World Series based on the probabilities of each team winning individual games.

---

## Usage

1. Include the desired header file in your C++ project:

```cpp
    #include "datastructs.hpp"
    #include "algorithms.hpp"
```

## Examples

### Example 1: Circular Dynamic Array

```cpp
    #include "datastructs.hpp"

    int main() {
        CircularDynamicArray<int> cda;
        cda.addEnd(10);
        cda.addFront(5);
        cda.addEnd(15);

        for (int i = 0; i < cda.length(); i++) {
            cout << cda[i] << " ";
        }
        return 0;
    }
```

### Example 2: Solving 0-1 Knapsack

```cpp
    #include "algorithms.hpp"

    int main() {
        int profits[] = {0, 60, 100, 120}; // 1-indexed
        int weights[] = {0, 10, 20, 30};  // 1-indexed
        int n = 3, maxWeight = 50;

        Knapsack knapsack(n, maxWeight, profits, weights);
        cout << "Maximum Profit: " << knapsack.getProfit() << endl;
        knapsack.printPWO();

        return 0;
    }
```
