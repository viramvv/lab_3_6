#include <gtest/gtest.h>
#include "Queue.h"

// Тест 1: Перевірка ініціалізації та порожнечі черги
TEST(QueueBasics, Initialization) {
    Queue q;
    init(q);
    EXPECT_TRUE(isEmpty(q));
    clear(q);
}

// Тест 2: Перевірка принципу FIFO (First In, First Out)
TEST(QueueBasics, EnqueueDequeueOrder) {
    Queue q;
    init(q);
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    EXPECT_EQ(dequeue(q), 10);
    EXPECT_EQ(dequeue(q), 20);
    EXPECT_EQ(dequeue(q), 30);
    EXPECT_TRUE(isEmpty(q));

    clear(q);
}

// Тест 3: Перевірка функції заповнення черги
TEST(LogicTests, FillQueueTest) {
    Queue q;
    init(q);
    fillPassengerQueue(q, 5); // Створюємо 5 пасажирів (0, 1, 2, 3, 4)

    EXPECT_EQ(dequeue(q), 0);
    EXPECT_EQ(dequeue(q), 1);

    clear(q);
}

// Тест 4: Перевірка ймовірності (математичний контроль)
// Хоча це симуляція, результат для 100 місць має бути близьким до 0.5
TEST(LogicTests, ProbabilityBoundaries) {
    const int SEATS = 100;
    const int RUNS = 1000; // Менше за 10к для швидкості тестів
    double success = 0;

    for(int i = 0; i < RUNS; ++i) {
        Queue q;
        init(q);
        fillPassengerQueue(q, SEATS);
        success += simulateBoarding(q, SEATS);
        clear(q);
    }

    double probability = success / RUNS;
    // Перевіряємо, чи ймовірність лежить в розумних межах похибки (0.4 - 0.6)
    EXPECT_NEAR(probability, 0.5, 0.1);
}

// Google Test сам надає точку входу, якщо підключений правильно,
// але зазвичай використовують такий макрос:
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}