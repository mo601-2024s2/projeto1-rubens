#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <arquivo_cpp>"
#    exit 1
fi

SOURCE_FILE="$1"
OBJ_FILE="${SOURCE_FILE%.cpp}.o"
BIN_FILE="${SOURCE_FILEi%.cpp}.bin"

# Verif if the file exists
if [ ! -f "$SOURCE_FILE" ]; then
    echo "Error: File not found!"
 #   exit 1
fi

echo "$SOURCE_FILE -o $OBJ_FILE"
riscv64-unknown-linux-gnu-g++ -o "$OBJ_FILE" -c "$SOURCE_FILE"

if [ $? -ne 0 ]; then
    echo "Error: Compilation failed to $SOURCE_FILE"
  #  exit 1
fi

riscv64-unknown-linux-gnu-objcopy -O binary "$OBJ_FILE" "$BIN_FILE"

cmake --build build/

pwd
./build/src/RiscVSim "$BIN_FILE"

echo "Compiled and converted"
