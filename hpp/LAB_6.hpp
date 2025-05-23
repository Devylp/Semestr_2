#pragma once
#include <iostream>
#include <stdexcept>

template <typename T, int Row, int Col>

class Matrix {

T** data;

public:
    // ����������� �� ��������� (�.� ��������� �� ���������� � ���� ���������)
    Matrix() {

        data = new T * [Row];

        for (int i = 0; i < Row; i++) {
            data[i] = new T[Col]{0};
        }
    }

    // ����������� �����������
    Matrix(const Matrix& other) : Matrix() // ����� ��� other Matrix()
    {
        // ������ �������� ������ �� other � �������������� �������
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

    // �������� ������������ ������������
    Matrix& operator=(Matrix other)
    {
        swap(*this, other);
        return *this;
    }
    // ��������������� ������� ��� ��������� ������������ ������������
    friend void swap(Matrix& a, Matrix& b) noexcept {
        std::swap(a.data, b.data);
    }

    // �������� ������ �� �������
    const T& operator () (int row, int col) const {
        if (row < 0 || row >= Row || col < 0 || col >= Col)
            std::out_of_range("Invalid index: Out of range");
        return data[row][col];
    }

    // �������� ��������� �������� �� �������
    T& operator () (int row, int col) {
        if (row < 0 || row >= Row || col < 0 || col >= Col)
            std::out_of_range("Invalid index: Out of range");
        return data[row][col];
    }

    // ��������� ������������ ������ (��������/���������)
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
    
    // ��������� ��������/��������� ������
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

    // �������� ��� ���������� ������������
    T Determinant() {
        //...
    }


    // �������� ����� �������
    friend std::istream& operator >> (std::istream& in, Matrix<T, Row, Col>& other) {
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                in >> other(i, j);
            }
        }
        return in;
    }

    // �������� ������ �������
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