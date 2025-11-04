# Universal Makefile for cross-platform compilation

# Detect operating system
ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname -s)
endif

# Compiler selection - try common compilers
CXX ?= g++
ifeq ($(detected_OS),Darwin)
    # On macOS, try to use Homebrew GCC if available, otherwise clang++
    ifeq (, $(shell which g++-13))
        ifeq (, $(shell which g++-12))
            ifeq (, $(shell which g++-11))
                CXX = clang++
            else
                CXX = g++-11
            endif
        else
            CXX = g++-12
        endif
    else
        CXX = g++-13
    endif
endif

# Platform-specific flags
ifeq ($(detected_OS),Windows)
    CXXFLAGS = -std=c++17 -O2
    EXE_EXT = .exe
else
    CXXFLAGS = -std=c++17 -O3
    EXE_EXT =
    ifneq ($(detected_OS),Darwin)
        CXXFLAGS += -march=native
    endif
endif

# Common source files
SRCDIR = src
SOURCES = $(SRCDIR)/main.cpp
TARGET_PREFIX = zhanhong_58

# Default target - detect and build appropriate version
all: detect_system
	@echo "Building for $(detected_OS) system"
	@echo "Using compiler: $(shell $(CXX) --version | head -n1)"
	$(MAKE) both

# Detect system and compiler
detect_system:
	@echo "Detected OS: $(detected_OS)"
	@echo "Using CXX: $(CXX)"

# Parallel version
parallel:
	$(CXX) $(CXXFLAGS) -DPARALLEL_VERSION $(SOURCES) -o $(TARGET_PREFIX)_parallel$(EXE_EXT)
	@echo "Build complete: $(TARGET_PREFIX)_parallel (Parallel version)"

# Linear version
linear:
	$(CXX) $(CXXFLAGS) -DLINEAR_VERSION $(SOURCES) -o $(TARGET_PREFIX)_linear$(EXE_EXT)
	@echo "Build complete: $(TARGET_PREFIX)_linear (Linear version)"

# Both versions
both:
	$(CXX) $(CXXFLAGS) -DPARALLEL_VERSION -DLINEAR_VERSION $(SOURCES) -o $(TARGET_PREFIX)_both$(EXE_EXT)
	@echo "Build complete: $(TARGET_PREFIX)_both (Both versions)"

# Debug version
debug:
	$(CXX) -std=c++17 -g -DDEBUG -DPARALLEL_VERSION $(SOURCES) -o $(TARGET_PREFIX)_debug$(EXE_EXT)

# Clean
clean:
	rm -f $(TARGET_PREFIX)_*$(EXE_EXT) *.o

# Run commands
run_parallel: parallel
	./$(TARGET_PREFIX)_parallel$(EXE_EXT)

run_linear: linear
	./$(TARGET_PREFIX)_linear$(EXE_EXT)

run_both: both
	./$(TARGET_PREFIX)_both$(EXE_EXT)

# Test compiler compatibility
test_compiler:
	@echo "Testing compiler compatibility..."
	$(CXX) --version
	@echo "C++17 support test:"
	@echo "int main() { return 0; }" | $(CXX) -std=c++17 -x c++ -o /dev/null - 2>/dev/null && echo "C++17: SUPPORTED" || echo "C++17: NOT SUPPORTED"

.PHONY: all detect_system parallel linear both debug clean run_parallel run_linear run_both test_compiler