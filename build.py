#!/usr/bin/env python3

import os
from optparse import OptionParser

def main():
    os.system("cd build && cmake .. && cmake --build .")

if __name__ == "__main__":
    main()