# Compiler settings
CXX = g++-13
CXXFLAGS = -std=c++17 -O3 -march=native
SRCDIR = src
SOURCES = $(SRCDIR)/main.cpp
TARGET_PREFIX = zhanhong_58

# Default target - build parallel version
all: parallel

# Parallel version
parallel:
	$(CXX) $(CXXFLAGS) -DPARALLEL_VERSION $(SOURCES) -o $(TARGET_PREFIX)_parallel
	@echo "Build complete: $(TARGET_PREFIX)_parallel (Parallel version)"

# Linear version
linear:
	$(CXX) $(CXXFLAGS) -DLINEAR_VERSION $(SOURCES) -o $(TARGET_PREFIX)_linear
	@echo "Build complete: $(TARGET_PREFIX)_linear (Linear version)"

# Build both versions (for performance comparison)
both:
	$(CXX) $(CXXFLAGS) -DPARALLEL_VERSION -DLINEAR_VERSION $(SOURCES) -o $(TARGET_PREFIX)_both
	@echo "Build complete: $(TARGET_PREFIX)_both (Includes both parallel and linear versions)"

# Debug version
debug:
	$(CXX) -std=c++17 -g -DDEBUG -DPARALLEL_VERSION $(SOURCES) -o $(TARGET_PREFIX)_debug

# Clean
clean:
	rm -f $(TARGET_PREFIX)_*

# Run parallel version
run_parallel: parallel
	./$(TARGET_PREFIX)_parallel

# Run linear version  
run_linear: linear
	./$(TARGET_PREFIX)_linear

# Run both versions (performance comparison)
run_both: both
	./$(TARGET_PREFIX)_both

.PHONY: all parallel linear both debug clean run_parallel run_linear run_both