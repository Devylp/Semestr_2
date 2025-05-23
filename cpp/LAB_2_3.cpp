#include <iostream>
#include <utility> // ��� std::pair
#include "Functions.hpp"


int main() {
    setlocale(LC_ALL, "Russian");

    int row, col;
    std::cin >> row >> col;
    int** A = CreateMatrix(row, col);
    std::pair<int, int> start(0, 0);
    std::pair<int, int> end(2, 2);

    int distance = BFS(A, row, col, start, end);

    if (distance != -1) {
        std::cout << "���������� ���������� �� (" << start.first << "," << start.second
            << ") �� (" << end.first << "," << end.second << ") �����: "
            << distance << std::endl;
    }
    else {
        std::cout << "���� �� (" << start.first << "," << start.second
            << ") �� (" << end.first << "," << end.second << ") �� ������."
            << std::endl;
    }

    DeleteMatrix(A, row);
}


/*
��� ���� ���� ��������� N�M (2<=N,M<=100). � ������ ������ ���� ��������� �������:
�.� - ����� ������; - 1
�#� - ������ ������; - 0
�S� - ��������� ������; - 2
�E� - �������� ������; - 3
�������� ��������, ������� ��������� �����������
���������� ����� ��� ����������� �� ��������� ������ � ��������.
���� ��� ������� ����������, �������� -1. ������ �� ��� �������� ������, ������� �������� �.� (� ��� ����� � �� ���������).
*/
