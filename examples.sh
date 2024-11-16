#!/bin/bash
TARGET_FOLDER=${1:-./build}
echo Target folder set to : $TARGET_FOLDER

cmake -Bbuild -GNinja .
cmake --build build

for i in 1582 1800 1900 2024
do
./build/calendar -y $i -o $TARGET_FOLDER/example_$i
done
