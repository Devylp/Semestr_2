#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <utility> // Для std::pair
#include <map>     // Для хранения расстояний или предшественников
#include "LAB_6.hpp"

// Функции для создания, печати и удаления матриц
int** CreateMatrix(int row, int col) {
    int** A = new int* [row];

    for (int i = 0; i < row; i++) {
        A[i] = new int[col];
    }

    for (int j = 0; j < row; j++)
        for (int k = 0; k < col; k++)
            std::cin >> A[j][k];

    return A;
}

void PrintMatrix(int** A, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            std::cout << A[i][j] << "\t";
        std::cout << std::endl;
    }
}

void DeleteMatrix(int** A, int row) {
    for (int i = 0; i < row; i++)
        delete[] A[i];

    delete[] A;
}


// Функция для проверки возможных путей для движения
// M - количество строк, N - количество столбцов
std::vector<std::pair<int, int>> CheckDirections(int** A, const std::pair<int, int>& CurrentCoords, int M, int N) {
    std::vector<std::pair<int, int>> path;

    for (int x = CurrentCoords.first - 1; x <= CurrentCoords.first + 1; ++x) {
        for (int y = CurrentCoords.second - 1; y <= CurrentCoords.second + 1; ++y) {

            // Пропускаем саму текущую ячейку (CurrentCoords)
            if (x == CurrentCoords.first && y == CurrentCoords.second) {
                continue;
            }

            if (x >= 0 && x < M && y >= 0 && y < N) {

                if (A[x][y] != 0) { // Предполагаем, что 0 - это препятствие
                    path.push_back({ x, y });
                }
            }
        }
    }
    return path;
}



int BFS(int** A, int M, int N, const std::pair<int, int>& start, const std::pair<int, int>& end) {
    std::vector<std::vector<bool>> visited(M, std::vector<bool>(N, false));

    // Очередь для BFS. Хранит пары: {координаты, расстояние от start}
    std::queue<std::pair<std::pair<int, int>, int>> q;

    // Если стартовая ячейка непроходима (0)
    if (A[start.first][start.second] == 0) {
        return -1; // Стартовая точка недоступна
    }

    // Добавляем стартовую ячейку в очередь и помечаем ее как посещенную
    q.push({ start, 0 });
    visited[start.first][start.second] = true;


    while (!q.empty()) {
        std::pair<std::pair<int, int>, int> current = q.front();
        q.pop();

        std::pair<int, int> currentCoords = current.first;
        int currentDist = current.second;

        // Если достигли конечной точки
        if (currentCoords.first == end.first && currentCoords.second == end.second) {
            return currentDist; // Возвращаем расстояние
        }

        // Получаем всех возможных соседей для текущей ячейки
        std::vector<std::pair<int, int>> neighbors = CheckDirections(A, currentCoords, M, N);

        for (const auto& neighborCoords : neighbors) {
            int nextX = neighborCoords.first;
            int nextY = neighborCoords.second;

            // Если сосед проходим (уже проверено в CheckDirections)
            // и еще не был посещен
            if (!visited[nextX][nextY]) {
                visited[nextX][nextY] = true;
                q.push({ {nextX, nextY}, currentDist + 1 });
            }
        }
    }

    return -1; // Путь не найден
}