#include <stdio.h>

int josephus(int n, int k)
{
  if (n == 1)
    return 0;
  return (josephus(n - 1, k) + k) % n;
}

int main()
{
  int n, k;
  scanf("%d %d", &n, &k);
  printf("%d\n", josephus(n, k) + 1);
}