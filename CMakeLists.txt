cmake_minimum_required(VERSION 3.10)
project(MotorVehicleCollisions)

set(CMAKE_CXX_STANDARD 17)

# Phase 1
#add_executable(test phase-1/Main.cpp phase-1/CollisionDataset.cpp)

# Enable OpenMP
find_package(OpenMP REQUIRED)
SET(OPENMP_CXX_FLAGS "-O3 -fopenmp")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OPENMP_CXX_FLAGS}")

# Phase 2a
#add_executable(test phase-2a/Main.cpp phase-2a/CollisionDataset.cpp)
#target_link_libraries(test OpenMP::OpenMP_CXX)

# Phase 2b
#add_executable(test phase-2b/Main.cpp phase-2b/CollisionDataset.cpp)
#target_link_libraries(test OpenMP::OpenMP_CXX)

# Phase 2c
#add_executable(test phase-2c/Main.cpp phase-2c/CollisionDataset.cpp)
#target_link_libraries(test OpenMP::OpenMP_CXX)

# Phase 3
add_executable(test phase-3/Main.cpp phase-3/CollisionDataset.cpp)
target_link_libraries(test OpenMP::OpenMP_CXX)