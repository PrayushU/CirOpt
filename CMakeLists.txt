cmake_minimum_required(VERSION 3.10)

# set the project name
project(Genetic_Algorithm)
# set the include path
include_directories(include)

# add the main code
add_subdirectory(src)

# If your main executable is in `src`, ignore this part
# Otherwise, define and link it here
# add_executable(MainExecutable main.cpp)
# target_link_libraries(MainExecutable CoreLib)

# add the tests
include(CTest)
enable_testing()
add_subdirectory(tests)


