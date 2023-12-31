cmake_minimum_required(VERSION 2.8)
project(extrapolation)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(GTKPlot gtkmm-plplot-2.0)
pkg_check_modules(PLPLOT plplot-c++)

if(WINDOWS_COMPILING)
     set(CMAKE_C_COMPILER "x86_64-w64-mingw32-gcc-win32")
     set(CMAKE_CXX_COMPILER "x86_64-w64-mingw32-g++-win32")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I. -std=c++17 -lwinpthread -static-libgcc -static-libstdc++")
else()
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

file(GLOB SOURCES CONFIGURE_DEPENDS
     "src/*.cpp"
     "src/Graphics/*.cpp"
)
set(INCLUDE include/)

link_directories(${GTKMM_LIBRARY_DIRS} ${GTKPlot_LIBRARY_DIRS} ${PLPLOT_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS} ${GTKPlot_INCLUDE_DIRS} ${PLPLOT_INCLUDE_DIRS} ${INCLUDE})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES} ${GTKPlot_LIBRARIES} ${PLPLOT_LIBRARIES})
