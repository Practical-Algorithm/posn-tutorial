#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: Advent of Code 2024 Day 1
 * Resource: https://adventofcode.com/2024/day/1
 * Topic: Sort
 */

int counting[100000];

int main()
{
  int n = 1000;
  vector<int> first;
  while (n--)
  {
    int x, y;
    cin >> x >> y;
    first.push_back(x);
    counting[y]++;
  }

  long long counter = 0;
  for (int i = 0; i < first.size(); i++)
  {
    counter += (long long)first[i] * (long long)counting[first[i]];
  }
  cout << counter << endl;
}