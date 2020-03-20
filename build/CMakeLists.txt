cmake_minimum_required(VERSION 2.8.11)
cmake_policy(SET CMP0048 NEW)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED  TRUE)
project(JumpTrading VERSION 1.0)
add_executable(matching
	../main.cpp
	../OrderBookLL.cpp
	../OrderBookRBT.cpp
	../ExecutionLogger.cpp
	../MessageParser.cpp
	../Logger.cpp)