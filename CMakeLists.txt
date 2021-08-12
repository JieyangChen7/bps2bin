cmake_minimum_required(VERSION 3.18)

project(decompress_tool)

set(ADIOS2_DIR /home/jieyang/opt/adios/lib/cmake/adios2)
find_package(ADIOS2 REQUIRED)
set(VTKm_DIR /home/jieyang/opt/vtkm/lib/cmake/vtkm-1.6)
find_package(VTKm REQUIRED)

add_executable(convert convert.cpp)
target_link_libraries(convert adios2::adios2 vtkm_io)