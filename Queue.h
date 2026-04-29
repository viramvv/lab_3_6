#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

// Структура вузла
struct Node {
    int seatNumber;
    Node* next;
};

// Структура самої черги
struct Queue {
    Node* first;
    Node* last;
};

// Прототипи функцій (згідно з умовою: кожна функція має свою назву)
void init(Queue& q);
bool isEmpty(Queue q);
void enqueue(Queue& q, int val); // Додати в чергу
int dequeue(Queue& q);          // Взяти з черги
void printQueue(Queue q);       // Вивести список на екран
void clear(Queue& q);

void fillPassengerQueue(Queue& q, int count);
double simulateBoarding(Queue& passengerQueue, int totalSeats);
int findRandomFreeSeat(bool plane[], int totalSeats);

#endif