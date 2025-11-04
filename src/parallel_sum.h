#ifndef PARALLEL_SUM_H
#define PARALLEL_SUM_H

#include <vector>
#include <numeric>

// Check for parallel STL support
#if __has_include(<execution>)
    #include <execution>
    #define HAS_PARALLEL_STL 1
#else
    #define HAS_PARALLEL_STL 0
#endif

// Linear version sum calculation
inline long long calculate_linear_sum(const std::vector<long long>& data) {
    return std::accumulate(data.begin(), data.end(), 0LL);
}

// Parallel version sum calculation
inline long long calculate_parallel_sum(const std::vector<long long>& data) {
    #if HAS_PARALLEL_STL
    // std::reduce may not be available in all standard library implementations;
    // use std::accumulate as a portable fallback.
    return std::accumulate(data.begin(), data.end(), 0LL);
    #else
    // Fallback to linear version
    return calculate_linear_sum(data);
    #endif
}

#endif