cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)

project(Calculator VERSION 1.0 LANGUAGES CXX)

set(QT_PACKAGES
  Core
  Quick
  QuickControls2
  Test
)

find_package(Qt6 6.4 REQUIRED COMPONENTS ${QT_PACKAGES})

foreach(PACKAGE ${QT_PACKAGES})
  list(APPEND QT_COMPILE_DEFINITIONS ${Qt6${PACKAGE}_COMPILE_DEFINITIONS})
  list(APPEND QT_COMPILE_OPTIONS ${Qt6${PACKAGE}_EXECUTABLE_COMPILE_FLAGS})
  list(APPEND QT_LIBRARIES Qt6::${PACKAGE})
endforeach()

qt_add_resources(QT_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/qml/resources.qrc)

# math_engine library
add_library(math_engine STATIC
  ${CMAKE_CURRENT_LIST_DIR}/src/math_engine.cpp
  ${CMAKE_CURRENT_LIST_DIR}/inc/math_engine.h
)
target_include_directories(math_engine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)
target_compile_features(math_engine PUBLIC cxx_std_17)
target_compile_options(math_engine PRIVATE -O1 -Wall -Wextra)
target_link_libraries(math_engine PUBLIC Qt6::Core)
set_property(TARGET math_engine PROPERTY AUTOMOC ON)

# Calculator application
add_executable(Calculator ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp ${QT_RESOURCES})
target_include_directories(Calculator PRIVATE ${CMAKE_CURRENT_LIST_DIR}/inc)
target_compile_options(Calculator PRIVATE ${QT_COMPILE_OPTIONS} --std=gnu++17 -O1 -Wall -Wextra)
target_compile_definitions(Calculator PRIVATE ${QT_COMPILE_DEFINITIONS})
target_link_libraries(Calculator PRIVATE ${QT_LIBRARIES} math_engine)
set_property(TARGET Calculator PROPERTY AUTOMOC ON)

# Enable testing
include(CTest)
enable_testing()
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
