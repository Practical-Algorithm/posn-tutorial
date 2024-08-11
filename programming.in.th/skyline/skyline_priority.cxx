#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: Skyline
 * Resource: https://programming.in.th/tasks/1008
 * Topic: Sort, Sweep Line
 */

struct Tower
{
  unsigned int l, h, r;
  Tower(unsigned int l, unsigned int h, unsigned int r) : l(l), h(h), r(r) {}

  bool operator<(const Tower &t) const
  {
    return h < t.h;
  }

  bool isAvailable(unsigned int x) const
  {
    return l <= x && x < r;
  }
};

int main()
{
  int nTower;
  scanf("%d", &nTower);
  vector<Tower> towers;
  vector<unsigned int> positions;

  for (int i = 0; i < nTower; i++)
  {
    int l, h, r;
    scanf("%d %d %d", &l, &h, &r);
    towers.push_back(Tower(l, h, r));
    positions.push_back(l);
    positions.push_back(r);
  }

  sort(towers.begin(), towers.end(), [](const Tower &a, const Tower &b)
       { return a.l < b.l; });
  sort(positions.begin(), positions.end());

  priority_queue<Tower> availableTowers;
  unsigned int currentTowerIndex = 0;
  unsigned int currentHeight = 0;
  for (unsigned int i = 0; i < positions.size(); i++)
  {
    unsigned int currentPosition = positions[i];
    while (!availableTowers.empty() && !availableTowers.top().isAvailable(currentPosition))
      availableTowers.pop();

    while (currentTowerIndex < towers.size() && towers[currentTowerIndex].l == currentPosition)
    {
      availableTowers.push(towers[currentTowerIndex]);
      currentTowerIndex++;
    }

    if (availableTowers.empty() && currentHeight != 0)
      printf("%d 0 ", currentPosition), currentHeight = 0;
    else if (!availableTowers.empty() && availableTowers.top().h != currentHeight)
      printf("%d %d ", currentPosition, availableTowers.top().h), currentHeight = availableTowers.top().h;
  }
}
