#include "../algorithms.hpp"

#include <cassert>

int main() {

    {   // Empty matrix chain; single matrix
        Matrix *A = new Matrix(2, 3);
        MatrixChain mc({A});
        Matrix *result = mc.solve();
        assert(result == A); // Multiplying a single matrix should return the matrix itself
        delete A;
    }

    // Error here
    {   // Two simple matrices
        Matrix* A = new Matrix(std::vector< std::vector<int> >{{1, 2}, {3, 4}});
        Matrix* B = new Matrix(std::vector< std::vector<int> >{{5, 6}, {7, 8}});
        MatrixChain mc({A, B});
        Matrix* result = mc.solve();
        Matrix* expected = new Matrix(std::vector< std::vector<int> >{{19, 22}, {43, 50}});
        for (int i = 0; i < result->col; i++) {
            for (int j = 0; j < result->row; j++) {
                assert(result->data[i][j] == expected->data[i][j]); // Compare content
            }
        }
        delete A; delete B; delete result; delete expected;
    }

    {   // Five matrices
        Matrix* A = new Matrix(std::vector< std::vector<int> >{{1, 2}, {3, 4}});
        Matrix* B = new Matrix(std::vector< std::vector<int> >{{5, 6}, {7, 8}});
        Matrix* C = new Matrix(std::vector< std::vector<int> >{{9, 10}, {11, 12}});
        Matrix* D = new Matrix(std::vector< std::vector<int> >{{13, 14}, {15, 16}});
        Matrix* E = new Matrix(std::vector< std::vector<int> >{{17, 18}, {19, 20}});
        std::vector<Matrix*> matrices = {A, B, C, D, E};
        MatrixChain mc(matrices);
        Matrix* result = mc.solve();
        Matrix* expected = new Matrix(std::vector< std::vector<int> >{{454917, 480142}, {1032089, 1089318}});
        for (int i = 0; i < result->col; i++) {
            for (int j = 0; j < result->row; j++) {
                assert(result->data[i][j] == expected->data[i][j]); // Compare content
            }
        }
        delete A; delete B; delete C; delete D; delete E; delete result; delete expected;
    }

    {   // Invalid matrix dimensions
        Matrix* A = new Matrix(2, 3);
        Matrix* B = new Matrix(4, 2);
        try {
            MatrixChain mc(std::vector<Matrix*>{A, B});
        } catch (const std::runtime_error &e) {
            assert(e.what() == std::string("Matrix dimensions do not match in MatrixChain constructor between matrices 0 and 1\nCol size of matrix 0 (3) != Row size of matrix 1 (4)\n"));
        }
        delete A; delete B;
    }

    return 0;
}