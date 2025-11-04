# zhanhong Student ID 58 - Parallel STL Array Sum Assignment

## Assignment Information
- **Name**: zhanhong
- **Student ID**: 58
- **Task**: Calculate sum of long long int array elements
- **Implementation**: Using C++ Parallel STL (std::reduce + std::execution::par)
- **Data Type**: long long int (64-bit integers)

## Build Instructions

### Using Makefile (Recommended)
```bash
# Build parallel version (default)
make parallel
./zhanhong_58_parallel

# Build linear version
make linear  
./zhanhong_58_linear

# Build both versions for performance comparison
make both
./zhanhong_58_both

# Run specific versions
make run_parallel    # Build and run parallel version
make run_linear      # Build and run linear version
make run_both        # Build and run both versions

# Clean build files
make clean