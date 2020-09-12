add_subdirectory(lib)
set(gtest_SOURCE_DIR, lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp GameCharacterTest.cpp GameCharcaterFixture.cpp TileMapTest.cpp UtilityTest.cpp MapSearchNodeTest.cpp)

add_executable(Google_Tests_run ${TEST_SOURCE_FILES})
target_link_libraries(Google_Tests_run gtest gtest_main core)