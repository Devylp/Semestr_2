/*
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

// Структура узла (без изменений)
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// Проверка на простое число
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// Проверка на нечетность
bool allDigitsOdd(int n) {
    if (n == 0) return false;
    if (n < 0) n = -n;
    while (n > 0) {
        if ((n % 10) % 2 == 0) return false;
        n /= 10;
    }
    return true;
}

// Проверка на четность
bool allDigitsEven(int n) {
    if (n < 0) n = -n;
    if (n == 0) return true; // Считаем 0 состоящим из четных цифр
    while (n > 0) {
        if ((n % 10) % 2 != 0) return false;
        n /= 10;
    }
    return true;
}

// Функции для работы со списком (передаем фиктивный узел)

// Добавление в конец (перед фиктивным узлом)
void insertTail(Node* dummy, int data) {
    Node* newNode = new Node(data);
    Node* lastNode = dummy->prev;
    newNode->next = dummy;
    newNode->prev = lastNode;
    lastNode->next = newNode;
    dummy->prev = newNode;
}

// Печать списка
void printList(Node* dummy) {
    if (dummy->next == dummy) { cout << "Список пуст.\n"; return; }
    cout << "Список: ";
    Node* current = dummy->next;
    while (current != dummy) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Удаление узла (возвращает следующий узел)
Node* deleteNode(Node* nodeToDelete) {
    if (nodeToDelete == nullptr || nodeToDelete->data == -1) return nullptr; // Защита от удаления dummy по значению
    Node* prevNode = nodeToDelete->prev;
    Node* nextNode = nodeToDelete->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    delete nodeToDelete;
    return nextNode;
}

// Вставка после узла
void insertAfter(Node* prevNode, int data) {
     if (prevNode == nullptr) return;
    Node* newNode = new Node(data);
    Node* nextNode = prevNode->next;
    newNode->prev = prevNode;
    newNode->next = nextNode;
    prevNode->next = newNode;
    nextNode->prev = newNode;
}

// Очистка памяти списка
void cleanupList(Node* dummy) {
    Node* current = dummy->next;
    while (current != dummy) {
        Node* nodeToDelete = current;
        current = current->next;
        delete nodeToDelete;
    }
    delete dummy; // Удаляем и сам фиктивный узел
    cout << "\nПамять списка очищена.\n";
}

// Проверка на наличие простого числа
bool containsPrime(Node* dummy) {
    Node* current = dummy->next;
    while (current != dummy) {
        if (isPrime(current->data)) return true;
        current = current->next;
    }
    return false;
}

// Сортировка по невозрастанию (пузырьком)
void sortListNonIncreasing(Node* dummy) {
    if (dummy->next == dummy || dummy->next->next == dummy) return; // Пуст или 1 элемент
    bool swapped;
    do {
        swapped = false;
        Node* current = dummy->next;
        while (current->next != dummy) {
            if (current->data < current->next->data) {
                swap(current->data, current->next->data); // Простой обмен данных
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

// Обработка: удаление "нечетных" / дублирование "четных"
void processListPrimesExist(Node* dummy) {
    Node* current = dummy->next;
    while (current != dummy) {
        Node* nextNode = current->next; // Запоминаем следующий заранее
        if (allDigitsOdd(current->data)) {
            deleteNode(current); // Удаляем текущий
        } else if (allDigitsEven(current->data)) {
            insertAfter(current, current->data); // Дублируем после текущего
            // Важно: current остается тем же узлом, nextNode указывает на следующий *оригинальный*
        }
        current = nextNode; // Переходим к следующему *оригинальному* узлу
    }
}

// --- Основная функция ---
int main() {
    setlocale(LC_ALL, "Russian");
    // Создаем фиктивный узел напрямую
    Node* dummy = new Node(-1); // Используем -1 как маркер фиктивного узла (хотя это не обязательно)
    dummy->next = dummy;
    dummy->prev = dummy;

    cout << "Введите натуральные числа (0 для конца):\n";
    int number;
    while (cin >> number && number != 0) {
        if (number > 0) {
            insertTail(dummy, number);
        } else if (number < 0) {
             cout << "Пропуск отрицательного числа.\n";
        }
         // Сброс ошибки и очистка буфера на случай некорректного ввода
         if (cin.fail() && number != 0) { // Доп. проверка, чтобы 0 не вызвал ошибку
            cout << "Ошибка ввода. Попробуйте снова.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
         }
    }
     // Очистка буфера после цикла на случай, если ввод завершился не числом, а потом 0
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    cout << "\nИсходный "; printList(dummy);

    if (!containsPrime(dummy)) {
        cout << "\nПростых нет. Сортировка...\n";
        sortListNonIncreasing(dummy);
    } else {
        cout << "\nЕсть простые. Обработка...\n";
        processListPrimesExist(dummy);
    }

    cout << "\nИтоговый "; printList(dummy);

    cleanupList(dummy); // Явно вызываем очистку памяти
}
*/