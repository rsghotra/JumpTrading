# JumpTrading
Order Matching Engine: Linked List based OrderBook implementation.

#How to Build
1. cd to directory where project is cloned. cd ../JumpTrading
2. cd build
3. Give the directory execution rights in case you see elavation issue. chmod 777 build
4. Build using CMAKE. On command terminal type: CMake .
5. On Windows: CMake by default will generate executable under /build/Debug
6. On Windows: Project will build in ../JumpTrading/build directory and executable will be in /build/Debug directory with name JumpTrading.
7. On MacOSX, Linux: CMake will generate a Make file in ../JumprTrading/build directory.
8. On MacOSX, Linux: When Make file is created. While you are in /build directory. Run make file by typing: make
9. On MacOSX, Linux: Executable will be generated in /build directory. With name JumpTrading

#How to run smoke tests supplied in testData/input directory.
1. Open shell on linux and cd to ../JumpTrading/testData
2. Execute test-runner.sh. Type ./test-runner.sh ; 
NOTE: if you see exe not found error. Then please edit line 12 of test-runner.sh file to point the program to the directory where your  executable have been generated. Typically - ../JumpTrading/build directory.
3. Tests will run and a new directory name output will be created.
4. Test runner matches each test's output data with pre-existing expected output data in /testData/expected directory.
5. If both files matches - test is declared passed else test is failed.
