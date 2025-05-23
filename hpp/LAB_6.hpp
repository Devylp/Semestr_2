#pragma once
#include <iostream>
#include <stdexcept>

template <typename T, int Row, int Col>

class Matrix {

T** data;

public:
    // Конструктор по умолчанию (т.е позволяет не передавать в себя аргументы)
    Matrix() {

        data = new T * [Row];

        for (int i = 0; i < Row; i++) {
            data[i] = new T[Col]{0};
        }
    }

    // Конструктор копирования
    Matrix(const Matrix& other) : Matrix() // Вызов для other Matrix()
    {
        // Теперь копируем данные из other в результирующую матрицу
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++)
                data[i][j] = other.data[i][j];
        }
    }

    ~Matrix() {
        for (int i = 0; i < Row; i++)
            delete[] data[i];

        delete[] data;
    }

    // Оператор присваивания копированием
    Matrix& operator=(Matrix other)
    {
        swap(*this, other);
        return *this;
    }
    // Вспомогательная функция для оператора присваивания копированием
    friend void swap(Matrix& a, Matrix& b) noexcept {
        std::swap(a.data, b.data);
    }

    // Оператор чтения по индексу
    const T& operator () (int row, int col) const {
        if (row < 0 || row >= Row || col < 0 || col >= Col)
            std::out_of_range("Invalid index: Out of range");
        return data[row][col];
    }

    // Оператор изменения значения по индексу
    T& operator () (int row, int col) {
        if (row < 0 || row >= Row || col < 0 || col >= Col)
            std::out_of_range("Invalid index: Out of range");
        return data[row][col];
    }

    // Операторы модификаторы матриц (сложение/умножение)
    Matrix& operator += (const Matrix& other) {
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++)
                data[i][j] += other(i, j);
        }
        return *this;
    }

    Matrix& operator *= (const T& scalar) {
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++)
                data[i][j] *= scalar;
        }
        return *this;
    }

    Matrix& operator ++ () {
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++)
                ++data[i][j];
        }
        return *this;
    }
    
    // Операторы сложения/умножения матриц
    Matrix operator + (const Matrix& other) const {
        Matrix temp = *this;
        temp += other;
        return temp;
    }
    
    template <int OtherCol>
    Matrix<T, Row, OtherCol> operator * (const Matrix<T, Col, OtherCol>& other) const {
        Matrix<T, Row, OtherCol> result;
        for (int i = 0; i < Row; ++i) {
            for (int j = 0; j < OtherCol; ++j) {
                result(i, j) = 0;
                for (int k = 0; k < Col; ++k) {
                    result(i, j) += data[i][k] * other(k, j);
                }
            }
        }
        return result;
    }

    // Оператор для вычисления определителя
    T Determinant() {
        //...
    }


    // Оператор ввода матрицы
    friend std::istream& operator >> (std::istream& in, Matrix<T, Row, Col>& other) {
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                in >> other(i, j);
            }
        }
        return in;
    }

    // Оператор вывода матрицы
    friend std::ostream& operator << (std::ostream& os, const Matrix<T, Row, Col>& other) {
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) 
                os << other(i, j) << " ";
            os << "\n";
        }
        return os;
    }

    T** ptr() const {
        return data;
    }
};