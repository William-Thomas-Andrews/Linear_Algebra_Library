#include "matrix.cpp"
#include <iostream>
#include <string>
#include <stdexcept> 
#include <vector>
#include <initializer_list>
#include <cmath>
#include <cstdlib>
#include <ranges>
#include <concepts> 
#include <iomanip>
#include <thread>
#include <future>
#include <type_traits>
#include <cassert>
#include <chrono>
#include <random>


int main() 
{
    std::cout << std::endl;
    std::vector<int> data({});
    for (int i = 1; i <= 10000; i++)
    {
        for (int j = 1; j <= 10000; j++)
        {
            data.push_back(i);
        }
    }


    std::cout << "Test Case 1: Simple 3x3 matrices: " << std::endl;
    std::vector<int> data1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix<int> A = Matrix<int>(data1, 3, 3);
    std::vector<int> data2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    Matrix<int> B = Matrix<int>(data2, 3, 3);
    Matrix C  = dotProduct(A, B);
    std::cout << C << std::endl;
    std::cout << std::endl;
    Matrix<int> E = dotProduct(C, C);
    std::cout << E << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Case 2: Simple 3x3 matrices: " << std::endl;
    std::vector<int> data5 = {1, 2, 3, 4, 5, 6, 7, 8, 9};  // Flattened 3x3 matrix
    std::vector<int> data6 = {-2, 1, 0, 1, -2, 1, 0, 1, -2};  // Flattened 3x3 matrix
    Matrix M = Matrix(data5, 3, 3);
    Matrix N = Matrix(data6, 3, 3);
    Matrix P  = dotProduct(M, N);
    std::cout << P << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Case 3: 4x3 dot 3x5: " << std::endl;
    std::vector<int> data3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};  // Flattened 4x3 matrix
    std::vector<int> data4 = {1, 0, 0, 0, 1, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9};  // Flattened 3x5 matrix
    Matrix<int> D = Matrix<int>(data3, 4, 3);
    Matrix<int> F = Matrix<int>(data4, 3, 5);
    Matrix<int> G = dotProduct(D, F);
    std::cout << G << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Case 4: Simple 3x3 matrix and identity: " << std::endl;
    std::vector<int> data7 = {
        1, 2, 3,  // First row
        4, 5, 6,  // Second row
        7, 8, 9   // Third row
    };
    // Flattened Matrix B (3x3)
    std::vector<int> data8 = {
        1, 0, 0,  // First row
        0, 1, 0,  // Second row
        0, 0, 1   // Third row
    };
    Matrix H = Matrix(data7, 3, 3);
    Matrix I = Matrix(data8, 3, 3);
    Matrix J = dotProduct(H, I);
    std::cout << J << std::endl;


    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Case 4: Double 2x2 matrices: " << std::endl;
    std::vector<double> data9 = {2.0808, 3, 1, 4};
    Matrix<double> matrix = Matrix<double>(data9, 2, 2);
    matrix.print();
    std::cout << std::endl;
    double a = 1.0, b = 4.0, c = 234.0, d = 34.424;
    double data10[4] = {a, b, c, d};
    Matrix<double> matrix2 = Matrix<double>(data10, 4, 2, 2);
    std::cout << std::endl;
    matrix2.print();
    std::cout << std::endl;
    Matrix<double> matrix3 = matrix + matrix2;
    std::cout << std::endl;
    matrix3.print();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << matrix3 << std::endl;


    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Case 5: Double 2x2 matrices added and subtracted: " << std::endl;
    Matrix<double> matrix4 = matrix2 + matrix;
    matrix4.print();
    std::cout << std::endl;
    Matrix<double> matrix5 = matrix2 - matrix;
    std::cout << std::endl;
    matrix5.print();
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Case 6: Double 2x2 matrix transposed: " << std::endl;
    matrix5.Transpose().print();
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Case 7: Double 2x2 matrix first element changed: " << std::endl;
    matrix5(0,0) = 14325342;
    std::cout << matrix5;
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Case 8: Using == and != " << std::endl;
    std::cout << (matrix5 == matrix4) << std::endl;
    std::cout << (matrix5 == matrix5) << std::endl;
    std::cout << (matrix5 != matrix4) << std::endl;
    std::cout << (matrix5 != matrix5) << std::endl;
    std::vector<int> data11 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix<int> intMatrix = Matrix(data11, 3, 3);
    std::vector<double> data12 = {10, 11, 12, 13, 14, 15, 16, 17, 18};
    Matrix<double> doubleMatrix = Matrix(data12, 3, 3);
    // std::cout << (intMatrix == doubleMatrix) << std::endl; // These int - double comparisons do not work
    // std::cout << (intMatrix == doubleMatrix) << std::endl;
    // std::cout << (intMatrix != doubleMatrix) << std::endl;
    // std::cout << (intMatrix != doubleMatrix) << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Case 9: Identity matrix and another matrix dot product" << std::endl;
    std::vector<int> data13 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix<int> matrix6 = Matrix<int>(data13, 3, 3);
    std::vector<int> data14 = {5, 6, 7, 8, 9, 10, 11, 12, 13};
    Matrix<int> matrix7 = Matrix<int>(data14, 3, 3);
    Matrix<int> matrix8 = dotProduct(matrix6, matrix7);
    std::cout << matrix8;
    std::cout << std::endl;
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Case 10: Matrix with all zeros dot product" << std::endl;
    std::vector<int> data15 = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    Matrix<int> matrix9 = Matrix<int>(data15, 3, 3);
    std::vector<int> data16 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix<int> matrix10 = Matrix<int>(data16, 3, 3);
    Matrix<int> matrix11 = dotProduct(matrix9, matrix10);
    std::cout << matrix11;
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Case 11: A matrix with negative and positive numbers" << std::endl;
    std::vector<int> data17 = {1, -2, 3, -4, 5, -6, 7, -8, 9};
    Matrix<int> matrix12 = Matrix<int>(data17, 3, 3);
    std::vector<int> data18 = {-1, 2, -3, 4, -5, 6, -7, 8, -9};
    Matrix<int> matrix13 = Matrix<int>(data18, 3, 3);
    Matrix<int> matrix14 = dotProduct(matrix12, matrix13);
    std::cout << matrix14;
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Case 12: Matrix with all ones" << std::endl;
    std::vector<int> data19 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    Matrix<int> matrix15 = Matrix<int>(data19, 3, 3);
    std::vector<int> data20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix<int> matrix16 = Matrix<int>(data20, 3, 3);
    Matrix<int> matrix17 = dotProduct(matrix15, matrix16);
    std::cout << matrix17 << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Case 13: Non-arithmetic matrices" << std::endl;
    std::vector<std::string> data21 = {"this", "is", "a", "matrix"};
    Matrix<std::string> matrix18 = Matrix<std::string>(data21, 2, 2);
    std::cout << matrix18 << std::endl;
    // matrix18 + matrix18; / Two non-arithmetic matrices cannot use arithmetic operations.

    return 0;
}