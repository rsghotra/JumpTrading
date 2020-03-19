cmake_minimum_required(VERSION 2.8.11)
cmake_policy(SET CMP0048 NEW)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED  TRUE)
project(JumpTrading VERSION 1.0)
add_executable(matching
	main.cpp
	OrderBookLL.cpp
	OrderBookRBT.cpp
	ExecutionLogger.cpp
	MessageParser.cpp
	Logger.cpp)

enable_testing()

add_test(NAME SimpleInput
	COMMAND bash -c "diff <( ./matching < ../testData/input/testSet0.txt) ../testData/output/testSet0.txt"
)

add_test(NAME SimpleInputWithAnError
	COMMAND bash -c "diff <( ./matching < ../testData/input/testSet1.txt) ../testData/output/testSet1.txt"
)

add_test(NAME TradeInMultipleOrdersSamePrice
	COMMAND bash -c "diff <( ./matching < ../testData/input/testSet2.txt) ../testData/output/testSet2.txt"
)

add_test(NAME TradeInMultipleOrdersMultiplePrice
	COMMAND bash -c "diff <( ./matching < ../testData/input/testSet3.txt) ../testData/output/testSet3.txt"
)

add_test(NAME GarbageInput
	COMMAND bash -c "diff <( ./matching < ../testData/input/testSet4.txt) ../testData/output/testSet4.txt"
)

add_test(NAME InvalidPrice
	COMMAND bash -c "diff <( ./matching < ../testData/input/testSet5.txt) ../testData/output/testSet5.txt"
)

add_test(NAME InvalidSize
	COMMAND bash -c "diff <( ./matching < ../testData/input/testSet6.txt) ../testData/output/testSet6.txt"
)

add_test(NAME InvalidId
	COMMAND bash -c "diff <( ./matching < ../testData/input/testSet7.txt) ../testData/output/testSet7.txt"
)

add_test(NAME InvalidAddOrderRequest
	COMMAND bash -c "diff <( ./matching < ../testData/input/testSet8.txt) ../testData/output/testSet8.txt"
)

add_test(NAME InvalidCancelOrderRequest
	COMMAND bash -c "diff <( ./matching < ../testData/input/testSet9.txt) ../testData/output/testSet9.txt"
)

add_test(NAME InvalidCancelRequestForFilledOrder
	COMMAND bash -c "diff <( ./matching < ../testData/input/testSet10.txt) ../testData/output/testSet10.txt"
)

add_test(NAME OutOfRangeInput
	COMMAND bash -c "diff <( ./matching < ../testData/input/testSet11.txt) ../testData/output/testSet11.txt"
)