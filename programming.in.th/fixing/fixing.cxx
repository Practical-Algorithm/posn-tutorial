#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: Fixing
 * Resource: https://programming.in.th/tasks/o61_mar_c2_fixing
 * Topic: Sorting, Greedy
 */

int main()
{
  int n, m, k;
  cin >> n >> m >> k;

  int leftmostBadTile = n;
  int rightmostBadTile = 0;

  vector<int> badTiles(m);
  for (int i = 0; i < m; i++)
  {
    cin >> badTiles[i];
    leftmostBadTile = min(leftmostBadTile, badTiles[i]);
    rightmostBadTile = max(rightmostBadTile, badTiles[i]);
  }

  int coveredGoodTiles = rightmostBadTile - leftmostBadTile + 1 - m;

  vector<int> goodTilesRange;
  for (int i = 0; i < m - 1; i++)
  {
    goodTilesRange.push_back(badTiles[i + 1] - badTiles[i] - 1);
  }
  sort(goodTilesRange.begin(), goodTilesRange.end(), greater<int>());

  int ans = coveredGoodTiles;
  for (int i = 0; i < k - 1 && i < (int)goodTilesRange.size(); i++)
  {
    ans -= goodTilesRange[i];
  }

  cout << ans << endl;
}