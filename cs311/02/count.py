import sys
import os
import functools
import operator
import re

filepath = "words.txt"
file = open(filepath, 'r')
words = file.read().split(',')
mx = 0
for i in range(0, len(words)):
	l = len(words[i].strip('"'))
	mx = l if l > mx else mx

print "MAXIMUM WORD LENGTH: "
print mx
print "WORDS OF THAT LENGTH:"
for i in range(0, len(words)):
	l = len(words[i].strip('"'))
	if l == mx:
		print words[i] 


