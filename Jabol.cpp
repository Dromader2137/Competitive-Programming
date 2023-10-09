#include<iostream>
#include<vector>
#include<utility>
#include<cstring>

std::vector<int> conn[1000003];
bool od1[1000003];
bool od2[1000003];
bool od3[1000003];
bool fab[1000003];

std::pair<int, int> tmd = {-1, -1};

int readInt () {
	bool minus = false;
	int result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true; else result = ch-'0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
	if (minus)
		return -result;
	else
		return result;
}

void DFS1(int x, int d)
{
	od1[x] = true;
	if (tmd.first < d and fab[x]) tmd = { d, x };

	for (int con : conn[x])
	{
		if (od1[con]) continue;

		DFS1(con, d + 1);
	}
}

void DFS2(int x, int d)
{
	od2[x] = true;
	if (tmd.first < d and fab[x]) tmd = { d, x };

	for (int con : conn[x])
	{
		if (od2[con]) continue;

		DFS2(con, d + 1);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);

	int N, K;

  N = readInt(); K = readInt();

	for (int i = 0; i < N - 1; ++i)
	{
		int a =readInt(), b = readInt();

		conn[a].push_back(b);
		conn[b].push_back(a);
	}
  
  int a;
  for(int i = 0; i < K; ++i)
  {
    a = readInt();

    fab[a] = true;
  }

	DFS1(a, 0);
	int wh = tmd.second;
	tmd = { -1, -1 };

  DFS2(wh, 0);

	std::cout << tmd.first;
}
