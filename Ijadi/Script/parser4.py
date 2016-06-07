#!/usr/bin/python
#return the needed line contains executable file name
import sys
from pyparsing import Word, alphanums
def toStr(buf):
    buffer = buf[0] 
    for i in range(1,len(buf)) :
        buffer = buffer + buf[i]
    return buffer

input_file = sys.argv[1]
input_exec_name = sys.argv[2]

f = open(input_file, "r")
list = f.readlines()

for i in range(0,len(input_file)-1) :
    if list[i].find("bin_PROGRAMS") != -1 :
        amtext = list[i]
        break

exec_name = Word( alphanums )

am_expr = Word("bin_PROGRAMS") + Word("=") + exec_name

am_parsed = am_expr.parseString(str(amtext))

ptext = am_parsed[2] 

for i in range(0,len(list)):
    list[i] = list[i].replace(ptext , input_exec_name)

print toStr(list)
    
