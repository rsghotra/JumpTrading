cmake_minimum_required(VERSION 2.8.11)
project (JumpTrading)

add_executable(matching
	main.cpp
	OrderBookLL.cpp
	OrderBookRBT.cpp
	ExecutionLogger.cpp
	MessageParser.cpp)

enable_testing()
add_test(test1
	./matching < ../testData/testSet1.txt
)
