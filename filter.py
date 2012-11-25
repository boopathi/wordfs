#!/usr/bin/python

f = open("./words")
for line in f:
    if len(line) > 2 and len(line) < 18:
        if "'" not in line:
            print line.lower(),

print
