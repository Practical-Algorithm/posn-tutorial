#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: TOI17_Junction
 * Resource: https://programming.in.th/tasks/toi17_junction
 * Topic: Graph, Tree, Binary Search
 */

struct EdgeTo
{
  int to, w;
  EdgeTo(int to, int w) : to(to), w(w) {}
};

vector<EdgeTo> adj[80005];
int subtreeWeight[80005];
int heavyChild[80005];
int totalWeight = 0;

void findHeavyLine(int currentNode, int parentNode, int &heavyRoot, int &branch)
{
  if (heavyRoot != -1)
    return;
  int heaviestSubtree = 0;
  int secondHeaviestSubtree = 0;
  int secondHaviestChild = -1;
  int childEdgeWeight = 0;

  for (EdgeTo edge : adj[currentNode])
  {
    if (edge.to == parentNode)
      continue;

    // DFS to every child (has only 2 children)
    findHeavyLine(edge.to, currentNode, heavyRoot, branch);
    childEdgeWeight += edge.w;
    int childSubtreeWeight = subtreeWeight[edge.to] + edge.w;
    subtreeWeight[currentNode] += childSubtreeWeight;

    if (childSubtreeWeight > heaviestSubtree)
    {
      // Update the second heaviest path
      secondHeaviestSubtree = heaviestSubtree;
      secondHaviestChild = heavyChild[currentNode];

      // Update the heaviest path
      heaviestSubtree = childSubtreeWeight;
      heavyChild[currentNode] = edge.to;
    }
    else if (childSubtreeWeight > secondHeaviestSubtree)
    {
      // Update the second heaviest path
      secondHeaviestSubtree = childSubtreeWeight;
      secondHaviestChild = edge.to;
    }
  }

  if (secondHeaviestSubtree != 0)
  {
    int rootSubtree = totalWeight - subtreeWeight[heavyChild[currentNode]] - subtreeWeight[secondHaviestChild] - childEdgeWeight;
    if (rootSubtree < secondHeaviestSubtree)
    {
      // The heavy path is not from the root
      heavyRoot = currentNode;
      branch = secondHaviestChild;
    }
  }
}

int LinearWeight[80005];
int BranchWeight[80005];

int Linearize(int currentNode, int parentNode, int index = 0)
{
  if (heavyChild[currentNode] == -1)
  {
    LinearWeight[index] = 0;
    BranchWeight[index] = 0;
    return index;
  }
  for (EdgeTo edge : adj[currentNode])
  {
    if (edge.to == parentNode)
      continue;
    if (heavyChild[currentNode] == edge.to)
    {
      LinearWeight[index] = edge.w;
    }
    else
    {
      BranchWeight[index] = subtreeWeight[edge.to] + edge.w;
    }
  }

  return Linearize(heavyChild[currentNode], currentNode, index + 1);
}

int main()
{
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    adj[u].push_back(EdgeTo(v, w));
    adj[v].push_back(EdgeTo(u, w));
    totalWeight += w;
  }
  for (int i = 0; i <= n; i++)
  {
    heavyChild[i] = -1;
  }

  int heavyRoot = -1;
  int branch = -1;

  int trueRoot = 0;
  findHeavyLine(0, -1, heavyRoot, branch);

  if (heavyRoot != -1)
  {
    int currentNode = heavyRoot;
    while (heavyChild[currentNode] != -1)
      currentNode = heavyChild[currentNode];
    trueRoot = currentNode;

    // printf("True root: %d\n", trueRoot);
    for (int i = 0; i <= n; i++)
      heavyChild[i] = -1, subtreeWeight[i] = 0;
    int dummyValue = -1;
    findHeavyLine(trueRoot, -1, dummyValue, dummyValue);
  }

  int index = Linearize(trueRoot, -1);
  // for (int i = 0; i < index; i++)
  // {
  //   printf("%d %d\n", LinearWeight[i], BranchWeight[i]);
  // }

  int left = 0;
  int right = totalWeight / 3;
  int answer = 0;
  while (left <= right)
  {
    int mid = (left + right) / 2;
    int componentCount = 0;
    int currentWeight = 0;
    for (int i = 0; i < index; i++)
    {
      if (BranchWeight[i] != 0)
        currentWeight += BranchWeight[i];

      if (currentWeight >= mid)
        currentWeight = 0, componentCount++;

      currentWeight += LinearWeight[i];
      if (currentWeight >= mid)
        currentWeight = 0, componentCount++;
    }

    if (componentCount >= 3)
      left = mid + 1, answer = mid;
    else
      right = mid - 1;
  }

  printf("%d\n", answer);
}

/**

Test case:
8
0 1 9
1 2 8
2 3 11
3 4 50
4 5 1
3 6 13
6 7 12
6 8 32


3 6 8 | 4 5


5
2 3 10
2 4 13
5 3 8
0 1 30
1 2 45


0 1 2 3 5


7
1 2 100
2 3 99
3 4 102
2 5 1
3 0 2
5 6 1
6 7 10

3 2 1 | 4


9
0 1 2
1 2 2
2 3 2
3 4 50
2 5 2
5 6 2
6 7 2
7 8 2
8 9 2


12
0 1 5
1 2 15
1 3 10
3 4 5
4 5 6
5 11 7
5 12 7
4 6 5
6 7 15
6 8 5
8 9 5
9 10 5

 */