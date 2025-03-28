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

Location skipWall(Location location, uint8_t direction)
{
  return Location(location.x + 2 * dx[direction], location.y + 2 * dy[direction]);
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

    for (uint8_t i = 0; i < 4; i++)
    {
      // Check clip wall
      Location skip = skipWall(current, i);
      if (skip.x >= 0 && skip.x < n && skip.y >= 0 && skip.y < n && !isWall(map, skip) && distance[skip.x][skip.y] != UINT16_MAX)
      {
        uint16_t newDistance = distance[skip.x][skip.y];
        uint16_t skipDistance = distance[current.x][current.y] - newDistance - 2;
        if (skipDistance >= 100)
        {
          printf("Skip: %d from %d %d to %d %d\n", skipDistance, current.x, current.y, skip.x, skip.y);
        }
      }

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
}