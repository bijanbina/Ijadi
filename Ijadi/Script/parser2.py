#!/usr/bin/python
#returns the executable file name that is merged in makefile.am
import sys
from pyparsing import Word, alphanums

input_text = sys.argv[1]

exec_name = Word( alphanums )

am_expr = Word("bin_PROGRAMS") + Word("=") + exec_name

am_parsed = am_expr.parseString(str(input_text))

print am_parsed[2]
