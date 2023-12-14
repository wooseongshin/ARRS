cmake_minimum_required(VERSION 3.27)
project(ARRS C)

set(CMAKE_C_STANDARD 11)

# List of source files for the library
set(LIBRARY_SOURCES
        src/input_interface.c
        src/controller.c
        src/service.c
        src/repository.c
)

# List of header files for the library
set(LIBRARY_HEADERS
        include/repository.h
        include/types.h
        include/service.h
        include/constants.h
        include/input_interface.h
)

# Create the library
add_library(ARRS STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

# Specify include directories for the library
target_include_directories(ARRS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create the main executable
add_executable(main src/main.c)

# Link the library to the main executable
target_link_libraries(main PRIVATE ARRS)