#include "Queue.h"
#include <ctime>
#include <cstdlib>

// Ініціалізація черги
void init(Queue& q) {
    q.first = nullptr;
    q.last = nullptr;
}

bool isEmpty(Queue q) {
    return q.first == nullptr;
}

// Додавання елемента
void enqueue(Queue& q, int val) {
    Node* newNode = new Node;
    newNode->seatNumber = val;
    newNode->next = nullptr;
    if (isEmpty(q)) {
        q.first = q.last = newNode;
    } else {
        q.last->next = newNode;
        q.last = newNode;
    }
}

// Вилучення з черги
int dequeue(Queue& q) {
    if (isEmpty(q)) return -1;
    Node* temp = q.first;
    int val = temp->seatNumber;
    q.first = q.first->next;
    if (q.first == nullptr) q.last = nullptr;
    delete temp;
    return val;
}

// Друкування списку
void printQueue(Queue q) {
    Node* curr = q.first;
    while (curr) {
        std::cout << curr->seatNumber << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

// Очищення пам'яті
void clear(Queue& q) {
    while (!isEmpty(q)) dequeue(q);
}

// Сформувати чергу з 100 пасажирів
void fillPassengerQueue(Queue& q, int count) {
    for (int i = 0; i < count; ++i) {
        enqueue(q, i); // Пасажири від 0 до 99
    }
}

 // Пошук вільного випадкового місця
// Ця функція допомагає реалізувати умову "сідає на будь-яке з вільних"
int findRandomFreeSeat(bool plane[], int totalSeats) {
    int freeCount = 0;
    for (int i = 0; i < totalSeats; ++i) {
        if (!plane[i]) freeCount++;
    }

    if (freeCount == 0) return -1;

    int targetIdx = rand() % freeCount;
    int currentFree = 0;
    for (int i = 0; i < totalSeats; ++i) {
        if (!plane[i]) {
            if (currentFree == targetIdx) return i;
            currentFree++;
        }
    }
    return -1;
}

// ПУНКТ 3: Основне моделювання посадки
double simulateBoarding(Queue& passengerQueue, int totalSeats) {
    bool* plane = new bool[totalSeats]{false}; // Масив місць (false - вільне)
    int lastPassengerSeat = -1;
    int passengerCount = 0;

    while (!isEmpty(passengerQueue)) {
        int ticket = dequeue(passengerQueue); // Пасажир бере свій білет і заходить
        int actualSeat;

        // ПЕРША УМОВА ВАРІАНТУ: Перший (старий чоловік) сідає випадково
        if (passengerCount == 0) {
            actualSeat = rand() % totalSeats;
        }
        else {
            // ДРУГА УМОВА ВАРІАНТУ: Наступні сідають на своє, якщо вільне
            if (!plane[ticket]) {
                actualSeat = ticket;
            } else {
                // Інакше — на будь-яке вільне
                actualSeat = findRandomFreeSeat(plane, totalSeats);
            }
        }

        plane[actualSeat] = true; // Займаємо місце

        if (isEmpty(passengerQueue)) {
            lastPassengerSeat = actualSeat; // Фіксуємо місце останнього
        }
        passengerCount++;
    }

    // Перевірка: чи сів останній (99-й) на своє (99-те) місце
    bool success = (lastPassengerSeat == totalSeats - 1);
    delete[] plane;
    return success ? 1.0 : 0.0;
}