cmake_minimum_required(VERSION 3.11)

project(time LANGUAGES CXX)

if(WIN32)
	set(PLATFORM TimeMeter_win.cpp)
else()
	set(PLATFORM TimeMeter_lin.cpp)
endif()

add_executable(main main.cpp ${PLATFORM})
