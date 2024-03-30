#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: Spyware
 * Resource: https://programming.in.th/tasks/codecube_035
 * Topic: Graph, Sorting
 */

int main()
{
  int n, m, k;
  cin >> n >> m >> k;

  vector<int> values(n + 1);
  for (int i = 1; i <= n; i++)
  {
    cin >> values[i];
  }

  vector<vector<int>> adjacencyList(n + 1);
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    adjacencyList[u].emplace_back(v);
    adjacencyList[v].emplace_back(u);
  }

  vector<int> spreadLevel(n + 1, -1);
  vector<vector<int>> nodesInSpreadLevel(n + 1);
  queue<int> q;
  spreadLevel[k] = 0;
  int maxSpreadLevel = 0;
  q.push(k);
  while (!q.empty())
  {
    int currentNode = q.front();
    q.pop();
    for (int v : adjacencyList[currentNode])
    {
      if (spreadLevel[v] == -1)
      {
        spreadLevel[v] = spreadLevel[currentNode] + 1;
        nodesInSpreadLevel[spreadLevel[v]].emplace_back(v);
        maxSpreadLevel = max(maxSpreadLevel, spreadLevel[v]);
        q.push(v);
      }
    }
  }

  long long answer = 0;
  priority_queue<int> valuesInSpreadLevel;
  for (int i = maxSpreadLevel; i >= 1; i--)
  {
    for (int node : nodesInSpreadLevel[i])
    {
      if (values[node] > 0)
        valuesInSpreadLevel.push(values[node]);
    }
    if (valuesInSpreadLevel.empty())
      continue;
    answer += (long long)valuesInSpreadLevel.top();
    valuesInSpreadLevel.pop();
  }

  // Not connected node
  for (int i = 1; i <= n; i++)
  {
    if (spreadLevel[i] == -1 && values[i] > 0)
      answer += values[i];
  }

  cout << answer << endl;
}
