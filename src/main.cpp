#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <numeric>

// Check for parallel STL support
#if __has_include(<execution>)
    #include <execution>
    #define HAS_PARALLEL_STL 1
#else
    #define HAS_PARALLEL_STL 0
    #pragma message("Parallel STL not available - falling back to sequential implementation")
#endif

int main() {
    const size_t array_size = 10000000; // 10 million elements
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
    long long linear_sum = std::accumulate(data.begin(), data.end(), 0LL);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> linear_duration = end - start;
    
    std::cout << "\n[Linear Version Results]" << std::endl;
    std::cout << "Array sum: " << linear_sum << std::endl;
    std::cout << "Computation time: " << linear_duration.count() << " seconds" << std::endl;
    #endif
    
    // Parallel version
    #ifdef PARALLEL_VERSION
    auto start_par = std::chrono::high_resolution_clock::now();
    long long parallel_sum = 0;
    
    #if HAS_PARALLEL_STL
    parallel_sum = std::reduce(std::execution::par, data.begin(), data.end(), 0LL);
    std::cout << "\n[Parallel STL Version Results]" << std::endl;
    #else
    // Fallback to linear if parallel STL not available
    parallel_sum = std::accumulate(data.begin(), data.end(), 0LL);
    std::cout << "\n[Fallback Linear Version Results (Parallel STL not available)]" << std::endl;
    #endif
    
    auto end_par = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> parallel_duration = end_par - start_par;
    
    std::cout << "Array sum: " << parallel_sum << std::endl;
    std::cout << "Computation time: " << parallel_duration.count() << " seconds" << std::endl;
    
    #ifdef LINEAR_VERSION
    // Performance comparison
    std::cout << "\n[Performance Comparison]" << std::endl;
    std::cout << "Speedup: " << linear_duration.count() / parallel_duration.count() << "x" << std::endl;
    #endif
    #endif
    
    // System and compiler info
    std::cout << "\n[System Info]" << std::endl;
    #if defined(_WIN32)
    std::cout << "Platform: Windows" << std::endl;
    #elif defined(__APPLE__)
    std::cout << "Platform: macOS" << std::endl;
    #elif defined(__linux__)
    std::cout << "Platform: Linux" << std::endl;
    #else
    std::cout << "Platform: Unknown" << std::endl;
    #endif
    
    #if HAS_PARALLEL_STL
    std::cout << "Parallel STL: Available" << std::endl;
    #else
    std::cout << "Parallel STL: Not Available" << std::endl;
    #endif
    
    return 0;
}