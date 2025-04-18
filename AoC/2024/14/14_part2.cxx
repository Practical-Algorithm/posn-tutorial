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
};

int main()
{
  setvbuf(stdout, NULL, _IONBF, 0);
  vector<Robot> robots;
  for (int i = 0; i < n; i++)
  {
    // p=24,28 v=-92,3
    int p1, p2, v1, v2;
    scanf("%d %d %d %d", &p1, &p2, &v1, &v2);
    robots.push_back(Robot(p1, p2, v1, v2));
  }

  int paint[tall][wide] = {0};

  for (int t = 0; t < 10000; t++)
  {
    for (int i = 0; i < robots.size(); i++)
    {
      robots[i].elapse(1);
      paint[robots[i].y][robots[i].x] = 1;
    }
    int count = 0;
    int consecutive = 0;
    int maxConsec = 0;
    for (int i = 0; i < tall; i++)
    {
      for (int j = 0; j < wide; j++)
      {
        if (paint[i][j])
        {
          count++;
          consecutive++;
        }
        else
        {
          consecutive = 0;
        }
        if (consecutive > maxConsec)
          maxConsec = consecutive;
      }
    }
    if (maxConsec > 10)
    {
      printf("Time: %d\n", t);
      for (int i = 0; i < tall; i++)
      {
        for (int j = 0; j < wide; j++)
        {
          if (paint[i][j])
            cout << "#";
          else
            cout << ".";
        }
        cout << endl;
      }
      printf("density: %d\n", count);
      printf("--------------------\n");
      system("pause");
    }
    for (int i = 0; i < tall; i++)
      for (int j = 0; j < wide; j++)
        paint[i][j] = 0;
  }
}