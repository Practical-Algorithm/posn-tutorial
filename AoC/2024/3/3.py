#  *
#  * Problem: Advent of Code 2024 Day 3
#  * Resource: https://adventofcode.com/2024/day/3
#  * Topic: Regex


import re

# Find the pattern of `mul([number],[number])`

inputStr = input()

pattern = re.compile(r'mul\((\d+),(\d+)\)')

matches = pattern.findall(inputStr)

sumAll = 0
for (a, b) in matches:
    sumAll += int(a) * int(b)

print(sumAll)
