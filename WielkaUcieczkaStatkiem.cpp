#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <set>

std::vector<std::pair<int, int64_t>> N[100007];
std::vector<std::pair<int, int64_t>> R[100007];
std::pair<int64_t, std::set<std::pair<int, int64_t>>> NDst[100007];
std::pair<int64_t, std::set<std::pair<int, int64_t>>> EDst[100007];
std::pair<int64_t, std::set<std::pair<int, int64_t>>> XDst[100007];
std::set<int> P;

int64_t Calc(int NN)
{
  int x = 1;
  int64_t res = 1e16;

  while(x != NN)
  {
    P.insert(x);

    if (EDst[x].second.size() == 0)
      return -1;
    if (EDst[x].second.size() > 1)
      return EDst[1].first;

    //std::cout << x << " " << res << "\n";

    for(auto n : N[x])
    {
      if(EDst[x].second.find({n.first, n.second}) != EDst[x].second.end()) continue;

      res = std::min(res, NDst[x].first + n.second + EDst[n.first].first);
    }

    x = (*EDst[x].second.begin()).first;
  }

  return (res >= (int64_t)1e16) ? -1 : res;
}

void CalcDst(int v, std::pair<int64_t, std::set<std::pair<int, int64_t>>>* dst, std::vector<std::pair<int, int64_t>>* G)
{
  std::priority_queue<std::pair<int64_t, int>> Q;
  dst[v].first = 0;
  Q.push({0, v});
  while (!Q.empty()) {
    auto akt = Q.top(); Q.pop();
    if(dst[akt.second].first < -akt.first) continue;
    for(auto x : G[akt.second])
    {
      if(dst[x.first].first > dst[akt.second].first + x.second)
      {
        dst[x.first].first = dst[akt.second].first + x.second;
        Q.push({-dst[x.first].first, x.first});
        dst[x.first].second = {{akt.second, x.second}};
      }
      else if(dst[x.first].first == dst[akt.second].first + x.second)
      {
        dst[x.first].second.insert({akt.second, x.second});
      }
    }
  }
}

int main()
{
  int NN, M;
  std::cin >> NN >> M;

  if(NN == 1 or M == 0)
  {
    std::cout << "-1";
    return 0;
  }

  for(int i = 0; i <= NN; ++i) EDst[i].first = 1e16;
  for(int i = 0; i <= NN; ++i) NDst[i].first = 1e16;
  for(int i = 0; i <= NN; ++i) XDst[i].first = 1e16;

  for (int i = 0; i < M; i++)
  {
    int a, b, c;
    std::cin >> a >> b >> c;

    N[a].push_back({b, c});
    R[b].push_back({a, c});
  }

  CalcDst(NN, EDst, R);
  CalcDst(1, NDst, N);
  CalcDst(NN, XDst, N);

 /*for(int i = 1; i <= NN; ++i)
  {
    std::cout << EDst[i].first << " " << NDst[i].first << " " << XDst[i].first << " => ";
    for(auto x : EDst[i].second) std::cout << x.first << " ";
    std::cout << "\n";
  }*/

  P.insert(NN);
  int64_t w = Calc(NN);
  if(w == -1 and NDst[NN].first != 1e16 and XDst[1].first != 1e16) w = 2*NDst[NN].first + XDst[1].first;
  for(int i = 1; i <= NN; ++i)
  {
    if(P.find(i) == P.end()) w = std::min(w, NDst[i].first + EDst[i].first);
  }
  std::cout << w;
}
