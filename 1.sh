#!/bin/bash

help() {
echo "Usage: $0 [OPTION]... SUFFIX SIZE DIR OUTFILE"
echo
echo "Merge into OUTFILE all files with SUFFIX whose size is less than SIZE bytes inside DIR and its subdirectories."
echo
echo "Options:"
echo "  -h, --help     show this help message and exit"
echo
echo "Exit status:"
echo " 0   if OK,"
echo " 1   if invalid arguments or missing parameters"
}

if [[ "$1" == "-h" || "$1" == "--help" ]]; then
    help
    exit 0
fi

if [ $# -ne 4 ]; then
    help
    exit 1
fi

suffix=$1
size=$2
dir=$3
outfile=$4

> "$outfile"

for f in $(find "$dir" -type f -name "*.$suffix")
do
    filesize=$(stat -c%s "$f")
    if [ "$filesize" -lt "$size" ]; then
        echo "adding $f"
        cat "$f" >> "$outfile"
    fi
done
