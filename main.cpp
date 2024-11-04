#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
//Author: Kit Magar
//Date: 11/03/2024
class Matrix {
private:
    std::vector<std::vector<int>> data;
    int rows, cols;

public:
    // Constructor
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data.resize(rows, std::vector<int>(cols, 0));
    }

    // Method to load data from a file
   void loadFromFile(const std::string &filename, int startLine) {
        std::ifstream file(filename);
        if (!file) throw std::runtime_error("Unable to open file.");

        // Skip lines until startLine
        std::string line;
        for (int i = 0; i < startLine; ++i) {
            std::getline(file, line);  // Discard these lines
        }

        // Read the next 'rows' lines to fill the matrix
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!(file >> data[i][j])) {
                    throw std::runtime_error("File data is insufficient for specified matrix size.");
                }
            }
        }
        file.close();
    }
    // Method to display the matrix
    void display() const {
        for (const auto &row : data) {
            for (const auto &elem : row) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }

    // Overload + operator for matrix addition
    Matrix operator+(const Matrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition.");
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Overload * operator for matrix multiplication
    Matrix operator*(const Matrix &other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrix multiplication requires the number of columns of the first matrix to equal the number of rows of the second.");
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Function to calculate sum of main and secondary diagonal elements
    int sumOfDiagonals() const {
        int mainDiagonalSum = 0, secondaryDiagonalSum = 0;
        for (int i = 0; i < rows; ++i) {
            mainDiagonalSum += data[i][i];
            secondaryDiagonalSum += data[i][rows - i - 1];
        }
        return mainDiagonalSum + secondaryDiagonalSum;
    }

    // Function to swap two rows
    void swapRows(int row1, int row2) {
        if (row1 >= rows || row2 >= rows || row1 < 0 || row2 < 0) {
            throw std::out_of_range("Row indices out of range.");
        }
        std::swap(data[row1], data[row2]);
    }
};
int main() {
    try {
        // Define matrix dimensions (based on sample data)
        int matrixSize = 4;
        Matrix matrixA(matrixSize, matrixSize);
        Matrix matrixB(matrixSize, matrixSize);

        // Load data from file into matrices
        matrixA.loadFromFile("matrix-data.txt",0);
        matrixB.loadFromFile("matrix-data.txt",4);

        std::cout << "Matrix A:" << std::endl;
        matrixA.display();

        std::cout << "\nMatrix B:" << std::endl;
        matrixB.display();

        // Add matrices
        Matrix sumMatrix = matrixA + matrixB;
        std::cout << "\nSum of Matrix A and Matrix B:" << std::endl;
        sumMatrix.display();

        // Multiply matrices
        Matrix productMatrix = matrixA * matrixB;
        std::cout << "\nProduct of Matrix A and Matrix B:" << std::endl;
        productMatrix.display();

        // Sum of diagonals
        int diagonalSum = matrixA.sumOfDiagonals();
        std::cout << "\nSum of the diagonals in Matrix A: " << diagonalSum << std::endl;

        // Swap rows
        std::cout << "\nMatrix A after swapping rows 0 and 1:" << std::endl;
        matrixA.swapRows(0, 1);
        matrixA.display();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
