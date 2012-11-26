#!/usr/bin/python

f = open("./words")
valid = lambda x: len(x)>2 and len(x)<18 and "'" not in x
lines = { line.lower().strip(): 1 for line in f if valid(line.lower().strip()) }
for key,value in lines.iteritems():
    print key

### OLD CODE
#lines = [ line.lower().strip() for line in f if valid(line.lower().strip())]
#for line in f:
#    if len(line) > 2 and len(line) < 18:
#        if "'" not in line:
#            lines.append(line.lower())
#lines.sort()
#for i in lines:
#   print i


