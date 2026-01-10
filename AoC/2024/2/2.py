#  *
#  * Problem: Advent of Code 2024 Day 2
#  * Resource: https://adventofcode.com/2024/day/2
#  * Topic: Normal Logic?

def checkIncreasing(numList):
    for i in range(len(numList)-1):
        diff = abs(numList[i] - numList[i+1])
        if numList[i] >= numList[i+1] or not (1 <= diff <= 3):
            return False
    return True


def checkValid(numList):
    return checkIncreasing(numList) or checkIncreasing(numList[::-1])


n = 1000
counter = 0
for i in range(n):
    nums = input().split(' ')
    nums = [int(x) for x in nums]
    # print(nums)

    if checkValid(nums):
        counter += 1

print(counter)
