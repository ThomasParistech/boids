add_executable(main ${COMMON_SOURCES} main.cpp)
target_link_libraries(main ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})