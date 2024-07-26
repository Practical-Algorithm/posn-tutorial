#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: Cars
 * Resource: https://programming.in.th/tasks/1105
 * Topic: Sort, Binary Search, Hashing
 */

int main()
{
  int n, k;
  scanf("%d %d", &n, &k);
  priority_queue<int, vector<int>, greater<int>> minHeap;
  for (int i = 0; i < n; i++)
  {
    int x;
    scanf("%d", &x);
    minHeap.push(x);

    if (minHeap.size() > k)
      minHeap.pop();
  }
  printf("%d\n", minHeap.top());
}
