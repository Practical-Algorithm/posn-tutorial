#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: Advent of Code 2024 Day 20 
 * Resource: https://adventofcode.com/2024/day/20
 * Topic: BFS
 */

const int16_t dx[] = {0, 0, 1, -1};
const int16_t dy[] = {1, -1, 0, 0};
const uint8_t n = 141;
int lo = 0;

struct Location
{
  int16_t x, y;
  Location(int16_t x, int16_t y) : x(x), y(y) {}
  Location(Location *location) : x(location->x), y(location->y) {}
};

bool isWall(char **map, Location location)
{
  return map[location.x][location.y] == '#';
}

void checkGoodWarp(Location location, char **map, uint16_t **distance, int distanceToWarp)
{
  set<int> used;
  for (int16_t i = -distanceToWarp; i <= distanceToWarp; i++)
  {
    for (int16_t j = -distanceToWarp; j <= distanceToWarp; j++)
    {
      if (i == 0 && j == 0)
        continue;
      int16_t cheatDistance = abs(i) + abs(j);
      if (cheatDistance > distanceToWarp)
        continue;

      Location warp = Location(location.x + i, location.y + j);
      if (warp.x >= 0 && warp.x < n && warp.y >= 0 && warp.y < n && !isWall(map, warp) && distance[warp.x][warp.y] != UINT16_MAX)
      {
        int newDistance = distance[warp.x][warp.y];
        int currentDistance = distance[location.x][location.y];

        if (newDistance > currentDistance)
          continue;

        int warpDistance = currentDistance - newDistance - cheatDistance;
        if (warpDistance <= 0)
          continue;
        if (warpDistance >= 100)
        {
          lo++;
        }
      }
    }
  }
  // if (used.size() > 0)
  // {
  //   printf("current: %d %d\n", location.x, location.y);
  //   printf("--\n");
  // }
}

void bfs(char **map, uint16_t **distance, Location *end)
{
  queue<Location> q;
  q.push(Location(end));
  distance[end->x][end->y] = 0;
  while (!q.empty())
  {
    Location current = q.front();
    q.pop();

    // Check clip wall
    checkGoodWarp(current, map, distance, 20);
    for (uint8_t i = 0; i < 4; i++)
    {

      Location next = Location(current.x + dx[i], current.y + dy[i]);
      if (next.x < 0 || next.x >= n || next.y < 0 || next.y >= n || isWall(map, next) || distance[next.x][next.y] != UINT16_MAX)
        continue;
      distance[next.x][next.y] = distance[current.x][current.y] + 1;
      q.push(next);
    }
  }
}

int main()
{
  Location *start, *end;
  char **map = (char **)calloc(n, sizeof(char *));
  for (uint8_t i = 0; i < n; i++)
  {
    map[i] = (char *)calloc(n, sizeof(char));
    fscanf(stdin, "%s", *(map + i));

    for (uint8_t j = 0; j < n; j++)
    {
      if (map[i][j] == 'S')
        start = new Location(i, j);
      else if (map[i][j] == 'E')
        end = new Location(i, j);
    }
  }

  uint16_t **distance = (uint16_t **)calloc(n, sizeof(uint16_t *));
  for (int16_t i = 0; i < n; i++)
  {
    distance[i] = (uint16_t *)calloc(n, sizeof(uint16_t));

    for (int16_t j = 0; j < n; j++)
      distance[i][j] = UINT16_MAX;
  }

  bfs(map, distance, end);
  printf("%d\n", lo);
}