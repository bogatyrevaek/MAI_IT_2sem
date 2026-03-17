#!/bin/bash

help() {
echo "Usage: $0 [OPTION]..."
echo
echo "Merge into OUTFILE all files with SUFFIX whose size is less than SIZE bytes."
echo
echo "Options:"
echo "  -h, --help              show this help message"
echo "  -s, --suffix SUFFIX     file suffix"
echo "  -z, --size SIZE         maximum file size in bytes"
echo "  -d, --directory DIR     directory to search (default: .)"
echo "  -o, --output FILE       output file"
}

directory="."

while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help) help; exit 0 ;;
        -s|--suffix) suffix=$2; shift 2 ;;
        -z|--size) size=$2; shift 2 ;;
        -d|--directory) directory=$2; shift 2 ;;
        -o|--output) outfile=$2; shift 2 ;;
        *) echo "Unknown option: $1"; help; exit 1 ;;
    esac
done

if [ -z "$suffix" ] || [ -z "$size" ] || [ -z "$outfile" ]; then
    help
    exit 1
fi

> "$outfile"

for f in $(find "$directory" -type f -name "*.$suffix"); do
    filesize=$(stat -c%s "$f")
    if [ "$filesize" -lt "$size" ]; then
        echo "adding $f"
        cat "$f" >> "$outfile"
    fi
done
