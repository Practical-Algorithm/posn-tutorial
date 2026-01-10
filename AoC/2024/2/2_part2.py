#  *
#  * Problem: Advent of Code 2024 Day 2
#  * Resource: https://adventofcode.com/2024/day/2
#  * Topic: DP

def checkPair(a, b):
    if a == -1 or b == -1:
        return True
    diff = abs(a - b)
    return a < b and 1 <= diff <= 3


def checkIncreasing(numList):
    numList = [-1] + numList + [-1]
    dp = [1000] * len(numList)
    dp[0] = 0

    for i in range(1, len(numList)):
        for j in range(1, 3):
            if checkPair(numList[i-j], numList[i]):
                dp[i] = min(dp[i], dp[i-j] + (j - 1))

    return dp[-1] <= 1


def checkValid(numList):
    return checkIncreasing(numList) or checkIncreasing(numList[::-1])


n = 1000
counter = 0
for i in range(n):
    nums = input().split(' ')
    nums = [int(x) for x in nums]

    counter += checkValid(nums)


print(counter)
