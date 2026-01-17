#include<stdio.h>
#include<math.h>
#include<vector>
#include<algorithm>
#include<utility>

int main()
{
  int n;
  std::vector<int> X, Y;
  std::vector<std::pair<int,int> > points;
  scanf("%d", &n);
  for(int i=0;i<n;i++)
  {
    int x,y;
    scanf("%d %d",&x,&y);
    int rotX = x - y;
    int rotY = x + y;
    points.emplace_back(rotX,rotY);
    X.emplace_back(rotX);
    Y.emplace_back(rotY);
  } 
  std::sort(X.begin(), X.end());
  std::sort(Y.begin(), Y.end());

  double medX = (n % 2) ? X[(n-1)/2] : (X[(n-1)/2] + X[(n-1)/2 + 1])/2;
  double medY = (n % 2) ? Y[(n-1)/2] : (Y[(n-1)/2] + Y[(n-1)/2 + 1])/2;
  double sum = 0;
  for(int i=0;i<n;i++)
  {
    double diffX = abs(points[i].first - medX);
    double diffY = abs(points[i].second - medY);
    // sum += diffX + diffY - std::min(diffX, diffY);
    sum += diffX + diffY;  
  }
  printf("%ld\n", std::llround(sum));
}
