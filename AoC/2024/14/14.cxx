#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: Advent of Code 2024 Day 14
 * Resource: https://adventofcode.com/2024/day/14
 * Topic: Math???
 */

const int n = 500;
const int tall = 103;
const int wide = 101;

struct Robot
{
  int x, y, vx, vy;
  Robot(int x, int y, int vx, int vy) : x(x), y(y), vx(vx), vy(vy) {}

  void elapse(int time)
  {
    x += vx * time;
    y += vy * time;
    x %= wide;
    if (x < 0)
      x += wide;
    y %= tall;
    if (y < 0)
      y += tall;
  }

  int quadrant()
  {
    if (x < wide / 2 && y < tall / 2)
      return 0;
    if (x > wide / 2 && y < tall / 2)
      return 1;
    if (x < wide / 2 && y > tall / 2)
      return 2;
    if (x > wide / 2 && y > tall / 2)
      return 3;
    return -1;
  }
};

int main()
{

  vector<Robot> robots;
  for (int i = 0; i < n; i++)
  {
    // p=24,28 v=-92,3
    int p1, p2, v1, v2;
    scanf("%d %d %d %d", &p1, &p2, &v1, &v2);
    robots.push_back(Robot(p1, p2, v1, v2));
  }

  long long q[4] = {0, 0, 0, 0};
  for (int i = 0; i < robots.size(); i++)
  {
    robots[i].elapse(100);
    int quad = robots[i].quadrant();
    if (quad != -1)
      q[quad]++;
  }

  printf("%lld\n", q[0] * q[1] * q[2] * q[3]);
}