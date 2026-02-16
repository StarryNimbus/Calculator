cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)

project(PykaUIUXTakeHome VERSION 1.0 LANGUAGES CXX)

set(QT_PACKAGES
  Core
  Quick
  QuickControls2
)

find_package(Qt6 6.4 REQUIRED COMPONENTS ${QT_PACKAGES})

foreach(PACKAGE ${QT_PACKAGES})
  list(APPEND QT_COMPILE_DEFINITIONS ${Qt6${PACKAGE}_COMPILE_DEFINITIONS})
  list(APPEND QT_COMPILE_OPTIONS ${Qt6${PACKAGE}_EXECUTABLE_COMPILE_FLAGS})
  list(APPEND QT_LIBRARIES Qt6::${PACKAGE})
endforeach()

qt_add_resources(QT_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/resources.qrc)

file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
file(GLOB HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.h")

add_executable(Calculator ${SOURCES} ${HEADERS} ${QT_RESOURCES})
target_compile_options(Calculator PRIVATE ${QT_COMPILE_OPTIONS} --std=gnu++17 -O1 -Wall -Wextra)
target_compile_definitions(Calculator PRIVATE ${QT_COMPILE_DEFINITIONS})
target_link_libraries(Calculator PRIVATE ${QT_LIBRARIES})
set_property(TARGET Calculator PROPERTY AUTOMOC ON)
