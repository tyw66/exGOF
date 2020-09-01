add_executable(singleton p01_singleton.cpp)

#链接多线程库
find_package(Threads)
target_link_libraries(singleton ${CMAKE_THREAD_LIBS_INIT})