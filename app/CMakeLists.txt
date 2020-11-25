add_executable(main ${COMMON_SOURCES} main.cpp)
target_link_libraries(main ${OpenCV_LIBS} ${Boost_LIBRARIES})