#include<stdio.h>
#include<cstdlib>
#include<queue>
#include<vector>
#include<set>
#include<tuple>
#include<algorithm>


int main()
{
  int n,m;
  scanf("%d %d",&n,&m);
  std::vector<int> eventPoints(2*m);
  std::vector<int> start(m), end(m);
  for(int i=0;i<m;i++)
  {
    int s,e;
    scanf("%d %d", &s, &e);
    eventPoints[2*i] = s;
    eventPoints[2*i+1] = e;
    start[i] = s;
    end[i] = e;
  }

  std::set<int> temp(eventPoints.begin(), eventPoints.end());
  eventPoints.assign(temp.begin(), temp.end());

  std::sort(start.begin(), start.end());
  std::sort(end.begin(), end.end());

  int startCounter = 0;
  int endCounter =0 ;
  int currentCount = 0;
  int maxCount = 0;
  for(unsigned int i=0;i<eventPoints.size();i++)
  {
    while(startCounter < m && start[startCounter] == eventPoints[i])
    {
      currentCount++;
      startCounter++;
    }
    maxCount = std::max(maxCount, currentCount);
    while(endCounter < m && end[endCounter] == eventPoints[i])
    {
      currentCount--;
      endCounter++;
    }
  }
  printf("%d\n", maxCount);

}
