add_executable(test_pso test_pso.cpp)

target_link_libraries(test_pso ${OpenCV_LIBS})

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY})