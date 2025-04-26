#include "../algorithms.hpp"

#include <cassert>

int main() {

    // Empty matrix chain; single matrix
    Matrix *A = new Matrix(2, 3);
    MatrixChain mc({A});
    Matrix *result = mc.solve();
    assert(result == A); // Multiplying a single matrix should return the matrix itself
    delete A;

    // Two simple matrices
    Matrix* A = new Matrix(vector< vector<int> >{{1, 2}, {3, 4}});
    Matrix* B = new Matrix(vector< vector<int> >{{5, 6}, {7, 8}});
    MatrixChain mc({A, B});
    Matrix* result = mc.solve();
    Matrix* expected = new Matrix(vector< vector<int> >{{19, 22}, {43, 50}});
    assert(*result == *expected); // Compare content
    delete A; delete B; delete result; delete expected;

    // Five matrices
    Matrix* A = new Matrix(vector< vector<int> >{{1, 2}, {3, 4}});
    Matrix* B = new Matrix(vector< vector<int> >{{5, 6}, {7, 8}});
    Matrix* C = new Matrix(vector< vector<int> >{{9, 10}, {11, 12}});
    Matrix* D = new Matrix(vector< vector<int> >{{13, 14}, {15, 16}});
    Matrix* E = new Matrix(vector< vector<int> >{{17, 18}, {19, 20}});
    MatrixChain mc({A, B, C, D, E});
    Matrix* result = mc.solve();
    Matrix* expected = new Matrix(vector< vector<int> >{{1530, 1740}, {3570, 4080}});
    assert(*result == *expected); // Compare content
    delete A; delete B; delete C; delete D; delete E; delete result; delete expected;

    // Invalid matrix dimensions
    Matrix* A = new Matrix(2, 3);
    Matrix* B = new Matrix(4, 2);
    try {
        MatrixChain mc({A, B});
    } catch (const runtime_error &e) {
        assert(string(e.what()) == "Matrix dimensions do not match in MatrixChain constructor between matrices 0 and 1\nRow size 2 != Col size 4\n");
    }
    delete A; delete B;

    return 0;
}