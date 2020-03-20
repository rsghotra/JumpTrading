# JumpTrading
Order Matching Engine: Linked List based OrderBook implementation.

#How to Build
1. cd to directory where project is cloned. cd ../JumpTrading
2. Create a new directory name 'build'. mkdir build
3. Build using CMAKK. On command terminal type: CMake ../build
4. Project will build in ../JumpTrading/build directory.

#How to run smoke tests supplied in testData/input directory.
1. Open shell on linux and cd to ../JumpTrading/testData
2. Execute test-runner.sh
3. Tests will run and a new directory name output will be created.
4. Test runner matches each test's output data with pre-existing expected output data in /testData/expected directory.
5. If both files matches - test is declared passed else test is failed.
