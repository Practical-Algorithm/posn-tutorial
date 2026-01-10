#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: Advent of Code 2024 Day 20 
 * Resource: https://adventofcode.com/2024/day/20
 * Topic: BFS
 */

const int16_t dx[] = {0, 0, 1, -1};
const int16_t dy[] = {1, -1, 0, 0};
const uint8_t n = 141;

struct Lock
{
  bool isKey;
  int *combination;

  void readKey()
  {
    char line[8];

    cin >> line;
    isKey = line[0] != '#';
    combination = (int *)calloc(5, sizeof(int));
    for (int i = 0; i < 5; i++)
      combination[i] = -1;

    for (int i = 0; i < 5; i++)
    {
      cin >> line;
      line[strcspn(line, "\n")] = 0;
      for (int j = 0; line[j]; j++)
      {
        if (!isKey)
        {
          if (line[j] == '.' && combination[j] == -1)
            combination[j] = i;
        }
        else
        {
          if (line[j] == '#' && combination[j] == -1)
            combination[j] = 5 - i;
        }
      }
    }
    for (int i = 0; i < 5; i++)
      if (combination[i] == -1)
        combination[i] = isKey ? 0 : 5;

    cin >> line;

    // cout << (isKey ? "Key" : "Lock")
    //      << "\t";
    // for (int i = 0; i < 5; i++)
    //   cout << combination[i] << " ";
    // cout << endl;
  }
  Lock() : isKey(false), combination(NULL) {}
};

int main()
{

  vector<Lock> locks;
  vector<Lock> keys;
  int n = 500;
  for (int i = 0; i < n; i++)
  {
    Lock l;
    l.readKey();

    if (l.isKey)
      keys.push_back(l);
    else
      locks.push_back(l);
  }

  int counter = 0;
  for (auto &l : locks)
  {
    for (auto &k : keys)
    {
      bool isMatched = true;
      for (int i = 0; i < 5; i++)
      {
        if (l.combination[i] + k.combination[i] > 5)
        {
          isMatched = false;
          break;
        }
      }

      if (isMatched)
      {
        counter++;
      }
    }
  }

  cout << counter << endl;
}