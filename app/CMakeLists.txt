add_executable(main ${COMMON_SOURCES} ${THIRD_PARTY_SOURCES} main.cpp)
target_link_libraries(main ${GLUT_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} Eigen3::Eigen)