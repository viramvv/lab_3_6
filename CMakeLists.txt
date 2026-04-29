cmake_minimum_required(VERSION 3.10)
project(AirplaneBoarding)

set(CMAKE_CXX_STANDARD 14)

# Пошук Google Test (зазвичай він встановлений у системі або через пакетний менеджер)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Створюємо бібліотеку з нашої логіки, щоб не дублювати код
add_library(QueueLib Queue.cpp Queue.h)

# Основна програма
add_executable(boarding_app main.cpp)
target_link_libraries(boarding_app QueueLib)

# Тести (UnitTest.cpp)
add_executable(unit_tests UnitTest.cpp)
target_link_libraries(unit_tests QueueLib ${GTEST_LIBRARIES} pthread)