#!/usr/bin/python
#return the needed line contains name of project
import sys

from pyparsing import Word, Optional, alphanums
def toStr(buf):
    buffer = buf[0] 
    for i in range(1,len(buf)) :
        buffer = buffer + buf[i]
    return buffer

input_file = sys.argv[1]
input_name = sys.argv[2]

f = open(input_file, "r")
list = f.readlines()

for i in range(0,len(input_file)-1) :
    if list[i].find("AC_INIT") != -1 :
        actext = list[i]
        break

name = Word( alphanums )
version =  Word ( alphanums + '.' )
bug_report = Word ( alphanums )
tar_name = Word ( alphanums )

ac_expr = Word('AC_INIT') + Word('(') + Word('[') + name + Word(']') + Word(',') + Word('[') + version + Word(']') + Optional(Word(',') + Word('[') + bug_report + Word(']')) + Optional(Word(',') + Word('[') + tar_name + Word(']')) + Word(')')

ac_parsed = ac_expr.parseString(str(actext))

ac_parsed[3] = input_name

#stick list elements together
buffer = toStr(ac_parsed) + "\n"

list[i] = buffer

print toStr(list)

