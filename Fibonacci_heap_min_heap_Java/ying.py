#!/usr/bin/python
import os
for i in range(1, 11):
	density=i*10
	str1 = 'java com/yingshe/MST -r '
	str2='1000 '
	str3='%d'%density
	print 'n=1000; density=' + str3 + '.'
	for j in range(1, 6):
		str=os.popen(str1+str2+str3).readlines()
		for b in str:
			print b,

for i in range(1, 11):
	density=i*10
	str1 = 'java com/yingshe/MST -r '
	str2='3000 '
	str3='%d'%density
	print 'n=3000; density=' + str3 + '.'
	for j in range(1, 6):
		str=os.popen(str1+str2+str3).readlines()
		for b in str:
			print b,

for i in range(1, 11):
	density=i*10
	str1 = 'java com/yingshe/MST -r '
	str2='5000 '
	str3='%d'%density
	print 'n=5000; density=' + str3 + '.'
	for j in range(1, 6):
		str=os.popen(str1+str2+str3).readlines()
		for b in str:
			print b,
