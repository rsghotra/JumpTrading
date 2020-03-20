#!/bin/bash

echo "Removing previous test-run directory, if exists."
rm -rf output
mkdir output

cd input
testCount=0;
echo "Starting test-suite."
for f in *; do
    echo "=======TestCase $f==========="
    ../../build/JumpTrading < $f > ../output/$f
    diff ../output/$f ../expected/$f
    if [[ $? -eq 0 ]]; then
        echo "Test $f passed"
        echo "Output Test Data => => => "
        cat ../output/$f
        echo "Expected Test Data <= <= <= "
        cat ../expected/$f
        echo "RESULT: PASSED!!"
done
