#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: Cars
 * Resource: https://programming.in.th/tasks/1105
 * Topic: Sort, Binary Search, Hashing
 */

bitset<2000001> carSpeed;
int main()
{
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i++)
  {
    int x;
    scanf("%d", &x);
    carSpeed[x] = 1;
  }
  for (int i = 2000000; i >= 0; i--)
  {
    if (carSpeed[i] && --k == 0)
    {
      printf("%d\n", i);
      break;
    }
  }
}
