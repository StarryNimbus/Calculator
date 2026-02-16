include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)

add_executable(example_test
  TestMathEngine.cpp
)

target_link_libraries(example_test
  PRIVATE
    GTest::gtest_main
    math_engine
)

include(GoogleTest)
gtest_discover_tests(example_test)
