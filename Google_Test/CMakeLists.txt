project(Google_Test)


add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES MapSearchNodeFixture.cpp MapSearchNodeTest.cpp runAllTests.cpp)
add_executable(Google_Test_run ${TEST_SOURCE_FILES})
target_link_libraries(Google_Test_run gtest gtest_main core)

