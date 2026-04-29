#include <iostream>
#include "Queue.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));
    const int SEATS = 100;
    const int SIMULATIONS = 10000; // Робимо багато спроб для точності

    std::cout << "Modeling process for 100 passengers..." << std::endl;

    double totalSuccess = 0;
    for (int i = 0; i < SIMULATIONS; ++i) {
        Queue q;
        init(q);

        // Виклик підпрограми формування
        fillPassengerQueue(q, SEATS);

        // Виклик підпрограми моделювання
        totalSuccess += simulateBoarding(q, SEATS);

        clear(q); // Обов'язково чистимо чергу
    }

    // Вивести результат на екран
    std::cout << "Probability that the last passenger sits in their seat: "
              << (totalSuccess / SIMULATIONS) << std::endl;

    return 0;
}