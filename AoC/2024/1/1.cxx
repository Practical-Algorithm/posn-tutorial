#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: Advent of Code 2024 Day 1
 * Resource: https://adventofcode.com/2024/day/1
 * Topic: Sort
 */

int main()
{
  int n = 1000;
  vector<int> first;
  vector<int> second;
  while (n--)
  {
    int x, y;
    cin >> x >> y;
    first.push_back(x);
    second.push_back(y);
  }

  sort(first.begin(), first.end());
  sort(second.begin(), second.end());

  long long counter = 0;
  for (int i = 0; i < first.size(); i++)
  {
    counter += abs(first[i] - second[i]);
  }
  cout << counter << endl;
}