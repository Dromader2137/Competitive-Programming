#include <iostream>
#include <vector>
#include <queue>

std::priority_queue<std::pair<int64_t, int>> Q;
std::priority_queue<std::pair<std::pair<int64_t, int>, std::pair<int64_t, int>>> BQ;
int T[200007];
int ANS[200007];

int main()
{
  int N; std::cin >> N;
 
  for(int i = 1; i <= N; ++i)
  {
    std::cin >> T[i];
  }

  int64_t SC = 0;
  for(int i = 1; i <= N; ++i)
  {
    int x = T[i];
    
    if(Q.empty())
    {
      if(BQ.empty())
      {
        Q.push({-x, i});
      }
      else if(-BQ.top().first.first < x)
      {
        std::pair<std::pair<int64_t, int>, std::pair<int64_t, int>> c = BQ.top(); BQ.pop();
        Q.push(c.first);
        c.first = {-x, i};
        BQ.push(c);

        //std::cout << "Added: " << c.first.first << " " << c.first.second << " to " << c.second.first << c.second.second << " change BQ\n";
      }
      else 
      {
        Q.push({-x, i});
      }
    }
    else 
    {
      if(BQ.empty() == true)//and (x > -Q.top().first))
      {
        if(x > -Q.top().first)
        {
          BQ.push({{-x, i},{Q.top().first, Q.top().second}});
          //std::cout << "Added: " << -x << " " << i << " to " << Q.top().first << Q.top().second << " to BQ\n";
          Q.pop();
        }
        else 
        {
          Q.push({-x, i});
        }
      }
      else if(x + BQ.top().second.first > -BQ.top().first.first + BQ.top().second.first and -Q.top().first > -BQ.top().first.first)
      {
        std::pair<std::pair<int64_t, int>, std::pair<int64_t, int>> c = BQ.top(); BQ.pop();
        Q.push(c.first);
        c.first = {-x, i};
        BQ.push(c);
        
        //std::cout << "Added: " << c.first.first << " " << c.first.second << " to " << c.second.first << c.second.second << " change BQ\n";
      }
      else if(x > -Q.top().first) 
      {
        BQ.push({{-x, i},Q.top()});
        //std::cout << "Added: " << -x << " " << i << " to " << Q.top().first << Q.top().second << " to BQ\n";
        Q.pop();
      }
      else 
      { 
        Q.push({-x, i});
      }
    }
  }

  while(!BQ.empty()) 
  {
    std::pair<std::pair<int64_t, int>, std::pair<int64_t, int>> c = BQ.top(); BQ.pop();
    SC += -c.first.first + c.second.first;
    ANS[c.first.second] = -1;
    ANS[c.second.second] = 1;
  }
  
  std::cout << SC << "\n";
  for(int i = 1; i <= N; ++i) std::cout << ANS[i] << " ";
}
