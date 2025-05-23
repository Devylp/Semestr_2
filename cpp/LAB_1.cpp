/*
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

// ��������� ���� (��� ���������)
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// �������� �� ������� �����
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// �������� �� ����������
bool allDigitsOdd(int n) {
    if (n == 0) return false;
    if (n < 0) n = -n;
    while (n > 0) {
        if ((n % 10) % 2 == 0) return false;
        n /= 10;
    }
    return true;
}

// �������� �� ��������
bool allDigitsEven(int n) {
    if (n < 0) n = -n;
    if (n == 0) return true; // ������� 0 ��������� �� ������ ����
    while (n > 0) {
        if ((n % 10) % 2 != 0) return false;
        n /= 10;
    }
    return true;
}

// ������� ��� ������ �� ������� (�������� ��������� ����)

// ���������� � ����� (����� ��������� �����)
void insertTail(Node* dummy, int data) {
    Node* newNode = new Node(data);
    Node* lastNode = dummy->prev;
    newNode->next = dummy;
    newNode->prev = lastNode;
    lastNode->next = newNode;
    dummy->prev = newNode;
}

// ������ ������
void printList(Node* dummy) {
    if (dummy->next == dummy) { cout << "������ ����.\n"; return; }
    cout << "������: ";
    Node* current = dummy->next;
    while (current != dummy) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// �������� ���� (���������� ��������� ����)
Node* deleteNode(Node* nodeToDelete) {
    if (nodeToDelete == nullptr || nodeToDelete->data == -1) return nullptr; // ������ �� �������� dummy �� ��������
    Node* prevNode = nodeToDelete->prev;
    Node* nextNode = nodeToDelete->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    delete nodeToDelete;
    return nextNode;
}

// ������� ����� ����
void insertAfter(Node* prevNode, int data) {
     if (prevNode == nullptr) return;
    Node* newNode = new Node(data);
    Node* nextNode = prevNode->next;
    newNode->prev = prevNode;
    newNode->next = nextNode;
    prevNode->next = newNode;
    nextNode->prev = newNode;
}

// ������� ������ ������
void cleanupList(Node* dummy) {
    Node* current = dummy->next;
    while (current != dummy) {
        Node* nodeToDelete = current;
        current = current->next;
        delete nodeToDelete;
    }
    delete dummy; // ������� � ��� ��������� ����
    cout << "\n������ ������ �������.\n";
}

// �������� �� ������� �������� �����
bool containsPrime(Node* dummy) {
    Node* current = dummy->next;
    while (current != dummy) {
        if (isPrime(current->data)) return true;
        current = current->next;
    }
    return false;
}

// ���������� �� ������������� (���������)
void sortListNonIncreasing(Node* dummy) {
    if (dummy->next == dummy || dummy->next->next == dummy) return; // ���� ��� 1 �������
    bool swapped;
    do {
        swapped = false;
        Node* current = dummy->next;
        while (current->next != dummy) {
            if (current->data < current->next->data) {
                swap(current->data, current->next->data); // ������� ����� ������
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

// ���������: �������� "��������" / ������������ "������"
void processListPrimesExist(Node* dummy) {
    Node* current = dummy->next;
    while (current != dummy) {
        Node* nextNode = current->next; // ���������� ��������� �������
        if (allDigitsOdd(current->data)) {
            deleteNode(current); // ������� �������
        } else if (allDigitsEven(current->data)) {
            insertAfter(current, current->data); // ��������� ����� ��������
            // �����: current �������� ��� �� �����, nextNode ��������� �� ��������� *������������*
        }
        current = nextNode; // ��������� � ���������� *�������������* ����
    }
}

// --- �������� ������� ---
int main() {
    setlocale(LC_ALL, "Russian");
    // ������� ��������� ���� ��������
    Node* dummy = new Node(-1); // ���������� -1 ��� ������ ���������� ���� (���� ��� �� �����������)
    dummy->next = dummy;
    dummy->prev = dummy;

    cout << "������� ����������� ����� (0 ��� �����):\n";
    int number;
    while (cin >> number && number != 0) {
        if (number > 0) {
            insertTail(dummy, number);
        } else if (number < 0) {
             cout << "������� �������������� �����.\n";
        }
         // ����� ������ � ������� ������ �� ������ ������������� �����
         if (cin.fail() && number != 0) { // ���. ��������, ����� 0 �� ������ ������
            cout << "������ �����. ���������� �����.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
         }
    }
     // ������� ������ ����� ����� �� ������, ���� ���� ���������� �� ������, � ����� 0
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    cout << "\n�������� "; printList(dummy);

    if (!containsPrime(dummy)) {
        cout << "\n������� ���. ����������...\n";
        sortListNonIncreasing(dummy);
    } else {
        cout << "\n���� �������. ���������...\n";
        processListPrimesExist(dummy);
    }

    cout << "\n�������� "; printList(dummy);

    cleanupList(dummy); // ���� �������� ������� ������
}
*/