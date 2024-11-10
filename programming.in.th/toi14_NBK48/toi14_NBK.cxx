#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: toi14_NBK48
 * Resource: https://programming.in.th/tasks/toi14_nbk48
 * Topic: DP, Binary Search
 */

struct Episode
{
  int totalCost;
  Episode(int totalCost) : totalCost(totalCost) {}
};

int main()
{
  int nEpisode, nQuery;
  scanf("%d %d", &nEpisode, &nQuery);
  vector<Episode> episodes;

  int totalCost = 0;
  for (int i = 0; i < nEpisode; i++)
  {
    int cost;
    scanf("%d", &cost);
    totalCost += cost;
    episodes.push_back(Episode(totalCost));
  }

  for (int i = nEpisode - 1; i >= 1; i--)
  {
    // If watching more episodes is cheaper, then we should watch more episodes
    if (episodes[i].totalCost < episodes[i - 1].totalCost)
    {
      episodes[i - 1].totalCost = episodes[i].totalCost;
    }
  }

  while (nQuery--)
  {
    int query;
    scanf("%d", &query);
    int lowerEpisode = 0, upperEpisode = nEpisode - 1;
    while (lowerEpisode <= upperEpisode)
    {
      int mid = (lowerEpisode + upperEpisode) / 2;
      if (episodes[mid].totalCost <= query)
        lowerEpisode = mid + 1;
      else
        upperEpisode = mid - 1;
    }

    printf("%d\n", lowerEpisode);
  }
}
