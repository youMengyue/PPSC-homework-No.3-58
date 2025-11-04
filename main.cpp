#include <iostream>
#include <vector>
#include <numeric> // Для std::reduce и std::accumulate
#include <random>
#include <chrono>

// Директива USE_PARALLEL будет передаваться компилятору через CMake.
// Если она определена, будет использован заголовок <execution> для параллельных алгоритмов.
#ifdef USE_PARALLEL
#include <execution>
#endif

// Функция для вывода информации о задании
void print_task_info() {
    std::cout << "========================================" << std::endl;
    std::cout << "Студент: 58" << std::endl;
    std::cout << "Задание: 3. Найти сумму массива" << std::endl;
    std::cout << "Метод: 5. Реализовать при помощи parallel stl" << std::endl;
    std::cout << "Тип данных: 3. long long int (64-bit)" << std::endl;
#ifdef USE_PARALLEL
    std::cout << "Режим сборки: Параллельный (Parallel STL)" << std::endl;
#else
    std::cout << "Режим сборки: Последовательный (Sequential)" << std::endl;
#endif
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
}

int main() {
    print_task_info();

    // Задаем параметры массива
    const size_t array_size = 500'000'000; // 500 миллионов элементов
    std::vector<long long> data;
    data.reserve(array_size);

    std::cout << "Генерация " << array_size << " случайных чисел (long long)..." << std::endl;

    // Генерация случайных данных
    auto start_gen = std::chrono::high_resolution_clock::now();
    std::mt19937_64 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<long long> distribution(1, 100);

    for (size_t i = 0; i < array_size; ++i) {
        data.push_back(distribution(generator));
    }
    auto end_gen = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> gen_duration = end_gen - start_gen;
    std::cout << "Генерация завершена за " << gen_duration.count() << " секунд." << std::endl << std::endl;


    std::cout << "Вычисление суммы..." << std::endl;
    long long sum = 0;
    
    // Запускаем таймер для вычисления суммы
    auto start_sum = std::chrono::high_resolution_clock::now();

#ifdef USE_PARALLEL
    // ПАРАЛЛЕЛЬНАЯ ВЕРСИЯ: используется std::reduce с политикой std::execution::par
    // std::reduce - это аналог std::accumulate, оптимизированный для параллельного выполнения.
    sum = std::reduce(std::execution::par, data.begin(), data.end(), 0LL);
#else
    // ПОСЛЕДОВАТЕЛЬНАЯ ВЕРСИЯ: используется обычный std::accumulate
    sum = std::accumulate(data.begin(), data.end(), 0LL);
#endif

    auto end_sum = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> sum_duration = end_sum - start_sum;

    std::cout << "Вычисление завершено за " << sum_duration.count() << " секунд." << std::endl;
    std::cout << "Итоговая сумма элементов массива: " << sum << std::endl;

    return 0;
}