#include <iostream>
int64_t dp[5007][5007];

int main()
{
  int N; std::cin >> N;
  std::string a; std::cin >> a;

  for(int i = N; i >= 1; --i)
  {
    for(int j = i; j <= N; ++j)
    {
      if(i == j) dp[i][j] = 1;
      else if(a[i - 1] == a[j - 1]) dp[i][j] = (dp[i][j - 1] + dp[i + 1][j] + 1100000018) % 1100000017;
      else dp[i][j] = (dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1] + 1100000017) % 1100000017;

      //std::cout << i << " " << j << " " << dp[i][j] << "\n";
    }
  }

  std::cout << dp[1][N];
}
