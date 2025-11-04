// When compiling with -DPARALLEL_VERSION
#ifdef PARALLEL_VERSION
    // This code will be compiled
    long long parallel_sum = calculate_parallel_sum(data);
#endif

// When compiling with -DLINEAR_VERSION  
#ifdef LINEAR_VERSION
    // This code will be compiled
    long long linear_sum = calculate_linear_sum(data);
#endif