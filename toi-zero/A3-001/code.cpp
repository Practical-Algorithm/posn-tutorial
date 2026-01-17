#include <stdio.h>
#include <stdint.h>
#include <cstring>

int A[1005], L[1005], B[1005], R[1005];
int weight[1005];
int total = 0;

int diff(int x, int y) {return (x < y) ? y - x: x-y;}
int w(int a, int l) {return (a == 0) ? weight[l]: l;}
int max(int x, int y) {return (x < y)? y:x;}
void calc(int branch) {
  if (weight[branch]) return;
  if (A[branch] == 0) calc(L[branch]);
  if (B[branch] == 0) calc(R[branch]);
  weight[branch] = max(w(A[branch], L[branch]), w(B[branch], R[branch])) * 2;
  total += diff(w(A[branch], L[branch]), w(B[branch], R[branch]));
}


int main() {
  int n;
  memset(weight, 0, sizeof(weight));
  scanf("%d", &n);
  for (int i = 1;i <= n; i++) {
    scanf("%d %d %d %d", A+i,L+i, B+i, R+i);
  }
  
  for (int i = 1; i <= n; i++) {
    calc(i);
  }
  printf("%d\n", total);
}
