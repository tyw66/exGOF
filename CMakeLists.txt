project(exPattern)

SET(CMAKE_CXX_STANDARD 11)#C++11支持


add_executable(singleton p01_singleton.cpp)
#链接多线程库
find_package(Threads)
target_link_libraries(singleton ${CMAKE_THREAD_LIBS_INIT})


add_executable(factory p02_factory.cpp)
