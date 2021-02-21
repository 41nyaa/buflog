#!/bin/sh
# This shell is for cpp linter and use Google's cpplint.py(https://code.google.com/p/google-styleguide/)
# as cpp linter.
RESULT_FILE=lintresult.txt

if [ -e $RESULT_FILE ]; then
    rm $RESULT_FILE
    touch $RESULT_FILE
fi

for file in `\find ./include -name '*.h'`; do
    python cpplint.py $file >> $RESULT_FILE 2>&1
done

for file in `\find ./src -name '*.h'`; do
    python cpplint.py $file >> $RESULT_FILE 2>&1
done

for file in `\find ./src -name '*.cpp'`; do
    python cpplint.py $file >> $RESULT_FILE 2>&1
done
