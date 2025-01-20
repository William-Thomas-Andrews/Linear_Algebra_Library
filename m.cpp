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
#include <variant>
#include <any>
#include <execution>
#include <algorithm>


template<typename G>
concept Arithmetic = std::is_arithmetic_v<G>;

template<typename Q>
concept NotArithmetic = !(std::is_arithmetic_v<Q>);


template <typename Z>
class Matrix
{
    private:
        Z* matrixArray;
        int size = 0;
        int rows = 0;
        int columns = 0;
        
    public:
        Matrix(int num_rows, int num_columns) : rows(num_rows), columns(num_columns), size(num_rows*num_columns)
        {
            
            matrixArray = new Z[size];
            for (int i = 0; i < size; i++)
            {
                matrixArray[i] = 0;
            }
        }
        Matrix(int item, int num_rows, int num_columns) : rows(num_rows), columns(num_columns), size(num_rows*num_columns)
        {
            matrixArray = new Z[size];
            for (int i = 0; i < size; i++)
            {
                matrixArray[i] = item;
            }
        }
        Matrix(const std::vector<Z>& data, int num_rows, int num_columns) : rows(num_rows), columns(num_columns), size(num_rows*num_columns)
        {
            if (data.size() != size)
            {
                throw std::invalid_argument("Size of array does not match dimension sizes.");
            }
            matrixArray = new Z[size];
            for (int i = 0; i < size; i++)
            {
                matrixArray[i] = data[i];
            }
        }
        Matrix(const Z* data, int data_size, int num_rows, int num_columns) : rows(num_rows), columns(num_columns), size(num_rows*num_columns)
        {
            if (data_size != size)
            {
                throw std::invalid_argument("Size of array does not match dimension sizes.");
            }
            matrixArray = new Z[size];
            for (int i = 0; i < size; i++)
            {
                matrixArray[i] = data[i];
            }
        }

        ~Matrix()
        {
            delete[] matrixArray;
        }

        void print()
        {
            std::cout << this->getString();
        }
        // Operators
        const Matrix<Z> operator+(const Matrix<Z>& other) requires Arithmetic<Z>
        {
            if (this->rows != other.rows)
            {
                throw std::invalid_argument("Row sizes must match to perform matrix addition.");
            }
            if (this->columns != other.columns)
            {
                throw std::invalid_argument("Column sizes must match to perform matrix addition.");
            }
            Matrix<Z> return_matrix = Matrix<Z>(this->matrixArray, this->size, this->rows, this->columns);
            for (int i = 0; i < this->size; i++)
            {
                return_matrix.matrixArray[i] += other.matrixArray[i];
            }
            return return_matrix;
        }
        Matrix<Z> operator-(const Matrix<Z>& other) requires Arithmetic<Z>
        {
            if (this->rows != other.rows)
            {
                throw std::invalid_argument("Row sizes must match to perform matrix addition.");
            }
            if (this->columns != other.columns)
            {
                throw std::invalid_argument("Column sizes must match to perform matrix addition.");
            }
            Matrix<Z> return_matrix = Matrix<Z>(this->matrixArray, this->size, this->rows, this->columns);
            for (int i = 0; i < this->size; i++)
            {
                return_matrix.matrixArray[i] -= other.matrixArray[i];
            }
            return return_matrix;
        }
        Matrix<Z> operator*(const Matrix<Z>& other) requires Arithmetic<Z>
        {
            if (this->rows != other.rows)
            {
                throw std::invalid_argument("Row sizes must match to perform matrix addition.");
            }
            if (this->columns != other.columns)
            {
                throw std::invalid_argument("Column sizes must match to perform matrix addition.");
            }
            Matrix<Z> return_matrix = Matrix<Z>(this->matrixArray, this->size, this->rows, this->columns);
            for (int i = 0; i < this->size; i++)
            {
                return_matrix.matrixArray[i] *= other.matrixArray[i];
            }
            return return_matrix;
        }
        Matrix<Z> operator/(const Matrix<Z>& other) requires Arithmetic<Z>
        {
            if (this->rows != other.rows)
            {
                throw std::invalid_argument("Row sizes must match to perform matrix addition.");
            }
            if (this->columns != other.columns)
            {
                throw std::invalid_argument("Column sizes must match to perform matrix addition.");
            }
            Matrix<Z> return_matrix = Matrix<Z>(this->matrixArray, this->size, this->rows, this->columns);
            for (int i = 0; i < this->size; i++)
            {
                return_matrix.matrixArray[i] /= other.matrixArray[i];
            }
            return return_matrix;
        }
        void operator=(const Matrix<Z>& other) 
        {
            if (this == &other) return;
            for (int i = 0; i < other.size; i++)
            {
                this->matrixArray[i] = other.matrixArray[i];
            }
            this->size = other.size;
            this->rows = other.rows;
            this->columns = other.columns;
        }
        bool operator==(const Matrix<Z>& other)
        {
            if ((this->rows != other.rows) || (this->columns != other.columns))
            {
                return false;
            }
            if (this->size != other.size)
            {
                return false;
            }
            for (int i = 0; i < other.size; i++)
            {
                if (this->matrixArray[i] != other.matrixArray[i])
                {
                    return false;
                }
            }
            return true;
        }
        bool operator!=(const Matrix<Z>& other)
        {
            if ((this->rows != other.rows) || (this->columns != other.columns))
            {
                return true;
            }
            if (this->size != other.size)
            {
                return true;
            }
            for (int i = 0; i < other.size; i++)
            {
                if (this->matrixArray[i] != other.matrixArray[i])
                {
                    return true;
                }
            }
            return false;
        }
        std::vector<Z> getData() const // a copy of the data
        {
            std::vector<int> vec({});
            for (int i = 0; i < size; i++)
            {
                vec.push_back(matrixArray[i]);
            }
            return vec;
        }
        std::string getString() requires Arithmetic<Z>// a copy of the data in a string format (originally arithmetic data)
        {
            std::string str = "";
            for (int i = 0; i < size; i++)
            {
                str += std::to_string(matrixArray[i]);
                str += " ";
                if ((((i+1) % columns) == 0) && (i != size-1))
                {
                    str += '\n';
                }
            }
            return str;
        }
        std::string getString() requires NotArithmetic<Z> // a copy of the data in a string format (originally not arithmetic data)
        {
            std::string str = "";
            for (int i = 0; i < size; i++)
            {
                str += matrixArray[i];
                str += " ";
                if ((((i+1) % columns) == 0) && (i != size-1))
                {
                    str += '\n';
                }
            }
            return str;
        }
        int get(int rowIndex, int colIndex)
        {
            if (rows <= rowIndex)
            {
                throw std::out_of_range("Row index out of range");
                return INT_MIN;
            }
            if (0 > rowIndex)
            {
                throw std::out_of_range("Row index cannot be negative");
                return INT_MIN;
            }
            if (columns <= colIndex)
            {
                throw std::out_of_range("Column index out of range");
                return INT_MIN;
            }
            if (0 > colIndex)
            {
                throw std::out_of_range("Column index cannot be negative");
                return INT_MIN;
            }
            return matrixArray[(rowIndex * columns) + colIndex];
        }
        Matrix<Z> Transpose()
        {
            Matrix<Z> B = Matrix<Z>(columns, rows);
            int bIndex = 0;
            for (int i = 0; i < columns; i++)
            {
                for (int j = i; j < i+(columns*rows); j+=columns)
                {
                    B.matrixArray[bIndex] = matrixArray[j];
                    bIndex++;
                }
            }
            return B;
        }
        Matrix<Z> operator()(int rowIndex) const
        {
            if (rows <= rowIndex)
            {
                throw std::out_of_range("Row index out of range");
                exit(1);
            }
            if (0 > rowIndex)
            {
                throw std::out_of_range("Row index cannot be negative");
                exit(1);
            }
            std::vector<Z> returnData = {};
            for (int i = 0; i < columns; i++)
            {
                returnData.push_back(matrixArray[i + rowIndex*columns]);
            }
            return Matrix(returnData, 1, columns);
        }
        Z& operator()(int rowIndex, int colIndex) const
        {
            if (rows <= rowIndex)
            {
                throw std::out_of_range("Row index out of range");
                exit(1);
            }
            if (0 > rowIndex)
            {
                throw std::out_of_range("Row index cannot be negative");
                exit(1);
            }
            if (columns <= colIndex)
            {
                throw std::out_of_range("Column index out of range");
                exit(1);
            }
            if (0 > colIndex)
            {
                throw std::out_of_range("Column index cannot be negative");
                exit(1);
            }
            return matrixArray[(rowIndex * columns) + colIndex];
        }
        std::ostream& printToStream(std::ostream& os) const
        {
            os << dataToStream(matrixArray, os);
            return os;
        }
        template <typename T>
        friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& A);
        friend Matrix<double> dotProduct(const Matrix<double>& A, const Matrix<double>& B);
        friend Matrix<int> dotProduct(const Matrix<int>& A, const Matrix<int>& B);
        friend Matrix<Z> transpose(const Matrix<Z>& A);
};

template <typename Z>
std::ostream& operator<<(std::ostream& os, Matrix<Z>& A)
{
    os << A.getString();
    return os;
}

Matrix<double> dotProduct(const Matrix<double>& A, const Matrix<double>& B)
{
    if (A.columns != B.rows)
    {
        throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows.");
    }
    Matrix<double> toReturn = Matrix<double>(A.rows, B.columns);
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < B.columns; j++)
        {
            for (int k = 0; k < B.rows; k++)
            {
                toReturn(i, j) += A(i, k) * B(k, j);
            }
        }
    }
    return toReturn;
}

Matrix<int> dotProduct(const Matrix<int>& A, const Matrix<int>& B)
{
    if (A.columns != B.rows)
    {
        throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows.");
    }
    Matrix<int> toReturn = Matrix<int>(A.rows, B.columns);
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < B.columns; j++)
        {
            for (int k = 0; k < B.rows; k++)
            {
                toReturn(i, j) += A(i, k) * B(k, j);
            }
        }
    }
    return toReturn;
}