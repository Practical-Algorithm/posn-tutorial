#include <stdio.h>
#include <stdint.h>
/**
 * Problem: Find The Distance
 * Resource: https://programming.in.th/tasks/1048
 * Topic: Bitmask
 */

int main()
{
  uint32_t n;
  uint8_t k;
  scanf("%hhu %u", &k, &n);
  uint64_t accumulatedDistance = 0;
  while (n)
  {
    accumulatedDistance += n;
    n >>= 1;
  }
  printf("%lu\n", accumulatedDistance);
}
