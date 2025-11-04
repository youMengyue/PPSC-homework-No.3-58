# Указываем минимальную требуемую версию CMake
cmake_minimum_required(VERSION 3.12)

# Задаем имя проекта
project(ParallelSumCalculator LANGUAGES CXX)

# Устанавливаем стандарт C++17, так как Parallel STL требует его
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Добавляем опцию для включения/выключения параллельного режима
# ON - параллельный, OFF - последовательный
option(USE_PARALLEL "Enable Parallel STL execution" ON)

# Определяем имя исполняемого файла
set(EXECUTABLE_NAME sum_calculator)

# Добавляем исполняемый файл, который будет собран из main.cpp
add_executable(${EXECUTABLE_NAME} main.cpp)

# Логика для управления режимами
if(USE_PARALLEL)
    # Если опция USE_PARALLEL включена
    message(STATUS "Parallel mode is ON. Compiling with Parallel STL support.")
    
    # Передаем компилятору директиву -DUSE_PARALLEL
    target_compile_definitions(${EXECUTABLE_NAME} PRIVATE USE_PARALLEL)

    # Для параллельных алгоритмов в GCC и Clang часто требуется библиотека
    # Intel TBB (Threading Building Blocks). CMake найдет ее.
    # MSVC (компилятор Visual Studio) имеет встроенную поддержку и не требует TBB.
    find_package(TBB)
    if(TBB_FOUND)
        message(STATUS "Intel TBB library found. Linking...")
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE TBB::tbb)
    else()
        # Если TBB не найдена, компиляция может пройти успешно (например, в MSVC),
        # но на Linux/macOS, скорее всего, завершится ошибкой.
        message(WARNING "Intel TBB not found. Parallel STL might not be available on this compiler (GCC/Clang).")
    endif()
else()
    # Если опция USE_PARALLEL выключена
    message(STATUS "Parallel mode is OFF. Compiling in sequential mode.")
endif()