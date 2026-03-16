#!/usr/bin/env python3

import os
import argparse

parser = argparse.ArgumentParser(
    description="Merge into one file all files with given suffix whose size is less than specified."
)

parser.add_argument("suffix", help="file suffix")
parser.add_argument("size", type=int, help="maximum file size in bytes")
parser.add_argument("directory", help="directory to search")
parser.add_argument("outfile", help="output file")

args = parser.parse_args()

suffix = args.suffix
size = args.size
directory = args.directory
outfile = args.outfile

with open(outfile, "w") as out:
    for root, dirs, files in os.walk(directory):
        for name in files:
            if name.endswith("." + suffix):
                path = os.path.join(root, name)
                filesize = os.path.getsize(path)

                if filesize < size:
                    print("adding", path)
                    with open(path, "r") as f:
                        out.write(f.read())
