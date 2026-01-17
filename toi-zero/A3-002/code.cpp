#include<stdio.h>
#include<math.h>

int main() {
  int n;
  scanf("%d", &n);
  int i = ceil(sqrt(n));
  printf("%d\n", (i - 1)*2 - ((i%2 == n%2)?0:1));
}
