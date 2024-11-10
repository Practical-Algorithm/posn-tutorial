#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: Equipped
 * Resource: https://programming.in.th/tasks/1036
 * Topic: Bitmask, DP
 */

int dp[1 << 8];

int main()
{
  int n, k;
  int work;
  scanf("%d %d", &n, &k);
  int targetWorkState = (1 << k) - 1;
  for (int i = 1; i <= targetWorkState; i++)
    dp[i] = 1e9;

  for (int i = 0; i < n; i++)
  {
    int cost, mask = 0;
    scanf("%d", &cost);
    for (int j = 0; j < k; j++)
    {
      scanf("%d", &work);
      mask |= work << j;
    }

    for (int workState = 0; workState <= targetWorkState; workState++)
    {
      dp[workState | mask] = min(dp[workState | mask], dp[workState] + cost);
    }
  }
  printf("%d", dp[targetWorkState]);
}
