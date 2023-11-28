#include <iostream>
#include <utility>
#include <vector>

std::vector<std::pair<int, int>> connections[500007];
std::pair<int, int> lcatable[500007][20];
std::pair<int, int> lawandorder[500007];

void LCA(int v, int prev, int prevWeight) {
	lcatable[v][0].first = prev;
	lcatable[v][0].second = prevWeight;
	for(int i = 0; i < 19; ++i) {
		lcatable[v][i + 1].first = lcatable[lcatable[v][i].first][i].first;
		lcatable[v][i + 1].second = std::max(lcatable[v][i].second,
											 lcatable[lcatable[v][i].first][i].second);
	}
}

int counter = 1;
void DFS(int v) {
	lawandorder[v].first = counter; counter++;
	for(auto x : connections[v]) {
		if(lawandorder[x.first].first != 0) continue;
		LCA(x.first, v, x.second);
		DFS(x.first);
	}
	lawandorder[v].second = counter; counter++;
}

bool subtree(int a, int b) {
	return lawandorder[a].first <= lawandorder[b].first and 
	   lawandorder[a].second >= lawandorder[b].first;
}

int getLCAPoint(int a, int b) {
	if(subtree(a, b))
		return a;
	if(subtree(b, a))
		return b;

	for(int i = 19; i >= 0; --i) {
		if(lcatable[a][i].first == 0) continue;	
		if(!subtree(lcatable[a][i].first, b))
			a = lcatable[a][i].first;
	}

	return lcatable[a][0].first;
}

int getLCABiggest(int a, int b) {
	if(a == b) return 0;
	int c = getLCAPoint(a, b);
	int max = -2000000000;

	for(int i = 19; i >= 0; --i) {	
		if(lcatable[a][i].first == 0) continue;	
		if(subtree(c, lcatable[a][i].first)) {
			max = std::max(max, lcatable[a][i].second);
			a = lcatable[a][i].first;
		}
	}
	for(int i = 19; i >= 0; --i) {
#ifdef DEBUG
		std::cout << i << ": " << b << " " << lcatable[b][i].first << " " << subtree(c, lcatable[b][i].first) << "\n";
#endif
		if(lcatable[b][i].first == 0) continue;	
		if(subtree(c, lcatable[b][i].first)) {
			max = std::max(max, lcatable[b][i].second);
			b = lcatable[b][i].first;
		}
	}
	return max;
}

int main() {
	std::ios_base::sync_with_stdio(0); std::cin.tie(0);
	int N; std::cin >> N;

	for(int i = 0; i < N - 1; ++i) {
		int a, b, w; std::cin >> a >> b >> w;
		connections[a].push_back({b, w});
		connections[b].push_back({a, w});
	}

	DFS(1);

#ifdef DEBUG
	std::cout << "\n";
	for(int i = 1; i <= N; ++i) {
		std::cout << i << ": ";
		for(int j = 0; j < 20; ++j)
			std::cout << lcatable[i][j].first << " ";
		std::cout << "\n";
	}
	std::cout << "\n";
	for(int i = 1; i <= N; ++i) {
		std::cout << i << ": ";
		for(int j = 0; j < 20; ++j)
			std::cout << lcatable[i][j].second<< " ";
		std::cout << "\n";
	}
	std::cout << "\n";	
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			std::cout << getLCAPoint(i, j);
		}
		std::cout << "\n";
	}
	std::cout << "\n";	
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			std::cout << getLCABiggest(i, j);
		}
		std::cout << "\n";
	}
#endif

	while(1) {
		int a, b;
		std::cin >> a;
		if(a == -1) return 0;
		std::cin >> b;

		std::cout << getLCABiggest(a, b) << "\n";
	}
}
