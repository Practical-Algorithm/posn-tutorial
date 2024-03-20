#include <stdio.h>

int main()
{
  char input[1000005];
  scanf("%s", input);

  int mod3 = 0, mod11 = 0;
  for (int i = 0; input[i]; i++)
  {
    mod3 *= 10;
    mod3 += input[i] - '0';
    mod3 %= 3;

    mod11 = (mod11 * 10 + input[i] - '0') % 11;
  }
  printf("%d %d\n", mod3, mod11);
}