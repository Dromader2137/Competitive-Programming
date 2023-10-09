#include <iostream>
#include <algorithm>

std::pair<int, int> P[200007];

int main() {
  int N; std::cin >> N;

  for(int i = 0; i < N; ++i)
    std::cin >> P[i].first >> P[i].second;

  std::sort(P, P + N);
  
  int sc = 1;
  int cEnd = P[0].second;
  for(int i = 1; i < N; ++i)
  {
    if(P[i].first >= cEnd)
    {
      cEnd = P[i].second;
      sc++;
    }
    else
    {
      if(P[i].second < cEnd) cEnd = P[i].second;
    }
  }

  std::cout << sc;
}
