cmake_minimum_required(VERSION 2.8.11)
project (JumpTrading)

add_executable(matching
	main.cpp
	OrderBookLL.cpp
	OrderBookRBT.cpp
	ExecutionLogger.cpp
	MessageParser.cpp
	Logger.cpp)

enable_testing()
add_test(NAME test0
	COMMAND sh -c ls
)

add_test(NAME test1
	COMMAND bash -c "diff <( ./matching < ../testData/input/testSet0.txt) ../testData/output/testSet0.txt"
)
