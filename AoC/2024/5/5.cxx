#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: Advent of Code 2024 Day 5
 * Resource: https://adventofcode.com/2024/day/5
 * Topic: Graph
 */

vector<vector<int>> g;
int depth[100];
int indeg[100];

void dag()
{
  queue<int> q;
  for (int i = 0; i < 100; i++)
  {
    if (indeg[i] == 0)
    {
      q.push(i);
      cout << "Push " << i << endl;
      depth[i] = 0;
    }
  }

  while (!q.empty())
  {
    int u = q.front();
    cout << u << endl;
    q.pop();
    for (int v : g[u])
    {
      indeg[v]--;
      cout << u << " " << v << indeg[v] << endl;
      if (indeg[v] == 0)
      {
        q.push(v);
        depth[v] = depth[u] + 1;
      }
    }
  }
}

int main()
{
  int m = 1176;
  int q = 194;

  int n = 100;

  for (int i = 0; i < n; i++)
    depth[i] = -1;
  g.resize(n);
  for (int i = 0; i < m; i++)
  {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
    indeg[y]++;
  }

  dag();

  for (int i = 0; i < n; i++)
  {
    cout << i << " " << depth[i] << endl;
  }
}