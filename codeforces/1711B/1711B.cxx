#include <stdio.h>
#include <stdlib.h>

int min(int x, int y) { return (x < y) ? x : y; }
void _handle_testcase()
{
  int n, m;
  scanf("%d %d", &n, &m);
  int ans = __INT_MAX__;
  int *deg = (int *)calloc(n + 5, sizeof(int));
  int *unhappiness = (int *)calloc(n + 5, sizeof(int));
  int *edgelist = (int *)calloc(2 * m + 5, sizeof(int));
  for (int i = 0; i < n; i++)
    scanf("%d", unhappiness + i + 1);
  for (int i = 0; i < m; i++)
  {
    scanf("%d %d", edgelist + 2 * i, edgelist + 2 * i + 1);
    deg[edgelist[2 * i]]++;
    deg[edgelist[2 * i + 1]]++;
  }
  for (int i = 1; i <= n; i++)
    if ((*(deg + i)) % 2 == 1)
      ans = min(ans, *(unhappiness + i));
  for (int i = 0; i < m; i++)
  {
    if (*(deg + *(edgelist + 2 * i)) % 2 == 0 && *(deg + *(edgelist + 2 * i + 1)) % 2 == 0)
      ans = min(ans, *(unhappiness + *(edgelist + 2 * i)) + *(unhappiness + *(edgelist + 2 * i + 1)));
  }
  free(deg);
  free(unhappiness);
  free(edgelist);
  printf("%d\n", (m % 2 == 0) ? 0 : ans);
}

int main()
{
  int testcase;
  scanf("%d", &testcase);
  while (testcase--)
  {
    _handle_testcase();
  }
}