#  *
#  * Problem: Advent of Code 2024 Day 3
#  * Resource: https://adventofcode.com/2024/day/3
#  * Topic: Regex


import re


inputStr = input()

# Find the pattern of `mul([number],[number])` or `do()` or `don't()`
pattern = re.compile(r'mul\((\d+),(\d+)\)|(do\(\))|(don\'t\(\))')


# pattern = re.compile(r'mul\((\d+),(\d+)\)')

matches = pattern.findall(inputStr)

sumAll = 0
flag = True
for (a, b, do, dont) in matches:
    if do:
        flag = True
    elif dont:
        flag = False
    elif flag:
        sumAll += int(a) * int(b)

print(sumAll)
print(matches)
