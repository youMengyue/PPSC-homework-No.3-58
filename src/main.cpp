#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <execution>
#include "parallel_sum.h"

int main() {
    const size_t array_size = 10000000;
    std::vector<long long> data(array_size);
    
    // Random number generation
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<long long> dis(1, 100);
    
    for (size_t i = 0; i < array_size; ++i) {
        data[i] = dis(gen);
    }
    
    std::cout << "=== zhanhong Student ID 58 - Parallel STL Array Sum Assignment ===" << std::endl;
    std::cout << "Array size: " << array_size << " elements" << std::endl;
    std::cout << "Data type: long long (64-bit integers)" << std::endl;
    std::cout << "Task: Calculate array sum using parallel STL" << std::endl;
    
    // Linear version
    #ifdef LINEAR_VERSION
    auto start = std::chrono::high_resolution_clock::now();
    long long linear_sum = calculate_linear_sum(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> linear_duration = end - start;
    
    std::cout << "\n[Linear Version Results]" << std::endl;
    std::cout << "Array sum: " << linear_sum << std::endl;
    std::cout << "Computation time: " << linear_duration.count() << " seconds" << std::endl;
    #endif
    
    // Parallel version
    #ifdef PARALLEL_VERSION
    auto start_par = std::chrono::high_resolution_clock::now();
    long long parallel_sum = calculate_parallel_sum(data);
    auto end_par = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> parallel_duration = end_par - start_par;
    
    std::cout << "\n[Parallel Version Results]" << std::endl;
    std::cout << "Array sum: " << parallel_sum << std::endl;
    std::cout << "Computation time: " << parallel_duration.count() << " seconds" << std::endl;
    
    #ifdef LINEAR_VERSION
    // Performance comparison
    std::cout << "\n[Performance Comparison]" << std::endl;
    std::cout << "Speedup: " << linear_duration.count() / parallel_duration.count() << "x" << std::endl;
    #endif
    #endif
    
    return 0;
}