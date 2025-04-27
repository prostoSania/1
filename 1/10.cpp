#include <iostream>
#include <vector>
#include <stdexcept>


class Matrix {
protected:
    int rows;
    int cols;

public:
    
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        if (rows <= 0 || cols <= 0) {
            throw std::invalid_argument("Количество строк и столбцов должно быть положительным.");
        }
    }

    
    virtual double getElement(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Индекс выходит за пределы матрицы.");
        }
        return 0.0; 
    }

    
    virtual ~Matrix() {}

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }
};


class IntMatrix : public Matrix {
private:
    std::vector<std::vector<int>> data;

public:
    
    IntMatrix(int rows, int cols) : Matrix(rows, cols), data(rows, std::vector<int>(cols, 0)) {}

    
    double getElement(int row, int col) const override {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Индекс выходит за пределы матрицы.");
        }
        return data[row][col];
    }

    
    void setElement(int row, int col, int value) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Индекс выходит за пределы матрицы.");
        }
        data[row][col] = value;
    }
};


class FloatMatrix : public Matrix {
private:
    std::vector<std::vector<double>> data;

public:
    
    FloatMatrix(int rows, int cols) : Matrix(rows, cols), data(rows, std::vector<double>(cols, 0.0)) {}

    
    double getElement(int row, int col) const override {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Индекс выходит за пределы матрицы.");
        }
        return data[row][col];
    }

    
    void setElement(int row, int col, double value) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Индекс выходит за пределы матрицы.");
        }
        data[row][col] = value;
    }
};

int main() {
    try {
        IntMatrix intMatrix(3, 4);
        intMatrix.setElement(1, 2, 10);
        std::cout << "Элемент IntMatrix: " << intMatrix.getElement(1, 2) << std::endl;

        FloatMatrix floatMatrix(2, 2);
        floatMatrix.setElement(0, 1, 3.14);
        std::cout << "Элемент FloatMatrix: " << floatMatrix.getElement(0, 1) << std::endl;

        
        std::cout << "Элемент FloatMatrix: " << floatMatrix.getElement(5, 0) << std::endl; 

    } catch (const std::out_of_range& e) {
        std::cerr << "Ошибка выхода за пределы: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
         std::cerr << "Ошибка аргумента: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}