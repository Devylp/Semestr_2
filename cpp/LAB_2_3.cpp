#include <iostream>
#include <utility> // ƒл€ std::pair
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
        std::cout << " ратчайшее рассто€ние от (" << start.first << "," << start.second
            << ") до (" << end.first << "," << end.second << ") равно: "
            << distance << std::endl;
    }
    else {
        std::cout << "ѕуть от (" << start.first << "," << start.second
            << ") до (" << end.first << "," << end.second << ") не найден."
            << std::endl;
    }

    DeleteMatrix(A, row);
}


/*
¬ам дано поле размерами NхM (2<=N,M<=100). ¬ каждой клетке пол€ наход€тс€ символы:
С.Т - можно пройти; - 1
С#Т - нельз€ пройти; - 0
СSТ - начальна€ клетка; - 2
СEТ - конечна€ клетка; - 3
Ќапишите алгоритм, который определит минимальное
количество шагов дл€ перемещени€ из начальной клетки в конечную.
≈сли это сделать невозможно, выведите -1. ’одить во все соседние клетки, которые отмечены С.Т (в том числе и по диагонали).
*/
