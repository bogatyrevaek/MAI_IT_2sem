#!/usr/bin/env python3

import os
import argparse

parser = argparse.ArgumentParser(
    description="Merge into one file all files with given suffix whose size is less than specified."
)

parser.add_argument("-s", "--suffix", required=True, help="file suffix")
parser.add_argument("-z", "--size", type=int, required=True, help="maximum file size in bytes")
parser.add_argument("-d", "--directory", default=".", help="directory to search (default: current directory)")
parser.add_argument("-o", "--output", required=True, help="output file")

args = parser.parse_args()

with open(args.output, "w") as out:
    for root, dirs, files in os.walk(args.directory):
        for name in files:
            if name.endswith("." + args.suffix):
                path = os.path.join(root, name)
                if os.path.getsize(path) < args.size:
                    print("adding", path)
                    with open(path, "r") as f:
                        out.write(f.read())
