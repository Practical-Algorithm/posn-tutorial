#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: Skyline
 * Resource: https://programming.in.th/tasks/1008
 * Topic: Sort, Sweep Line
 */

struct Tower
{
  unsigned int position, h;
  bool isStart;
  Tower(unsigned int position, unsigned int h, bool isStart = true) : position(position), h(h), isStart(isStart) {}

  bool operator<(const Tower &t) const
  {
    return position < t.position;
  }
};

int main()
{
  int nTower;
  scanf("%d", &nTower);
  vector<Tower> towers;

  for (int i = 0; i < nTower; i++)
  {
    int l, h, r;
    scanf("%d %d %d", &l, &h, &r);
    towers.push_back(Tower(l, h));
    towers.push_back(Tower(r, h, false));
  }

  sort(towers.begin(), towers.end());
  multiset<unsigned int> heights;

  unsigned int currentHeight = 0;
  for (unsigned int i = 0; i < towers.size(); i++)
  {
    if (towers[i].isStart)
    {
      heights.insert(towers[i].h);
    }
    else
    {
      heights.erase(heights.find(towers[i].h));
    }

    unsigned int newHeight = heights.empty() ? 0 : *heights.rbegin();
    if (newHeight != currentHeight && (i == towers.size() - 1 || towers[i].position != towers[i + 1].position))
    {
      printf("%u %u ", towers[i].position, newHeight);
      currentHeight = newHeight;
    }
  }
}
