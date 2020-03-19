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

add_test(NAME test1
	COMMAND bash -c "diff <( ./matching < ../testData/input/testSet0.txt) ../testData/output/testSet0.txt"
)

# does the application run
add_test(NAME Runs COMMAND Tutorial 25)

# does the usage message work?
add_test(NAME Usage COMMAND Tutorial)
set_tests_properties(Usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
  )

# define a function to simplify adding tests
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction(do_test)

# do a bunch of result based tests
do_test(Tutorial 4 "4 is 2")
do_test(Tutorial 9 "9 is 3")
do_test(Tutorial 5 "5 is 2.236")
do_test(Tutorial 7 "7 is 2.645")
do_test(Tutorial 25 "25 is 5")
do_test(Tutorial -25 "-25 is [-nan|nan|0]")
do_test(Tutorial 0.0001 "0.0001 is 0.01")