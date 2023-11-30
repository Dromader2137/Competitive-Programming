/*
 *
 *	In Progress - Don't use!!!
 *
 */

#include <iostream>
#include <queue>
#include <utility>
#include <vector>

bool table[1007][1007];
int prefixV[1007][1007];
int prefixH[1007][1007];
int biggestSquare[1007][1007];
std::vector<std::pair<int, int>> connections[1000007];
std::pair<int, int> lcatable[1000007][20];
std::pair<int, int> lawandorder[1000007];
int subtreeTable[1000007];

std::priority_queue<std::pair<int, std::pair<std::pair<int, int>, std::pair<int, int>>>> Q;
std::pair<int, int> boss[1007][1007];

std::pair<int, int> find(std::pair<int, int> a) {
	if(boss[a.first][a.second] == a) return a;
	boss[a.first][a.second] = find(boss[a.first][a.second]);
	return boss[a.first][a.second];
}

void unionize(std::pair<int, int> a, std::pair<int, int> b) {
	std::pair<int, int> ai = find(a), bi = find(b);
	if(ai == bi) return;
	boss[ai.first][ai.second] = bi;
}

int pointToArray(int a, int b, int n) {
	return (b - 1) * n + a;
}

void LCA(int v, int prev, int prevWeight) {
	lcatable[v][0].first = prev;
	lcatable[v][0].second = prevWeight;
	for(int i = 0; i < 19; ++i) {
		lcatable[v][i + 1].first = lcatable[lcatable[v][i].first][i].first;
		lcatable[v][i + 1].second = std::min(lcatable[v][i].second,
											 lcatable[lcatable[v][i].first][i].second);
	}
}

int subtreeCounter = 1;
int counter = 1;
void DFS(int v) {
	subtreeTable[v] = subtreeCounter;
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
	int max = 10000;

	for(int i = 19; i >= 0; --i) {	
		// std::cout << c << " " << a << " " << i << " " << lcatable[a][i].second << " " << lcatable[a][i].first << "\n";
		if(lcatable[a][i].first == 0) continue;	
		if(subtree(c, lcatable[a][i].first)) {
			max = std::min(max, lcatable[a][i].second);
			a = lcatable[a][i].first;
		}
	}
	for(int i = 19; i >= 0; --i) {
		// std::cout << c << " " << b << " " << i << " " << lcatable[b][i].second << " " << lcatable[b][i].first << "\n";
		if(lcatable[b][i].first == 0) continue;	
		if(subtree(c, lcatable[b][i].first)) {
			max = std::min(max, lcatable[b][i].second);
			b = lcatable[b][i].first;
		}
	}
	return max;
}

int main() {
	std::ios_base::sync_with_stdio(0); std::cin.tie(0);
	int N; std::cin >> N;

	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			boss[j][i] = {j, i};
			char x; std::cin >> x;
			prefixH[j][i] = prefixH[j - 1][i];
			prefixV[j][i] = prefixV[j][i - 1];
			table[j][i] = (x == '#');
			prefixH[j][i] += table[j][i];
			prefixV[j][i] += table[j][i];
		}
	}
	

	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			int maxW = std::min(std::min(i - 1, j - 1), std::min(N - i, N - j));
			int w;
			for(w = std::max(1, biggestSquare[i][j - 1] - 2); w / 2 <= maxW; w += 2) {
				bool t = (prefixH[j - w / 2 - 1][i - w / 2] == prefixH[j + w / 2][i - w / 2]);
				bool b = (prefixH[j - w / 2 - 1][i + w / 2] == prefixH[j + w / 2][i + w / 2]);
				bool l = (prefixV[j - w / 2][i - w / 2 - 1] == prefixV[j - w / 2][i + w / 2]);
				bool r = (prefixV[j + w / 2][i - w / 2 - 1] == prefixV[j + w / 2][i + w / 2]);
				
				if(t and b and l and r) biggestSquare[j][i] = w;
				else break;
			}
			if(biggestSquare[j][i] == 0 and !table[j][i]) biggestSquare[j][i] = 1;
		}
	}

	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			if(biggestSquare[j][i] >= 1 and !table[j][i]) {
				if(i > 1 and !table[j][i - 1]) Q.push({std::min(biggestSquare[j][i], biggestSquare[j][i - 1]),{{j, i},{j, i - 1}}});
				if(i < N and !table[j][i + 1]) Q.push({std::min(biggestSquare[j][i], biggestSquare[j][i + 1]),{{j, i},{j, i + 1}}});
				if(j > 1 and !table[j - 1][i]) Q.push({std::min(biggestSquare[j][i], biggestSquare[j - 1][i]),{{j, i},{j - 1, i}}});
				if(j < N and !table[j + 1][i]) Q.push({std::min(biggestSquare[j][i], biggestSquare[j + 1][i]),{{j, i},{j + 1, i}}});
			}
			// std::cout << biggestSquare[j][i];
		}
		// std::cout << "\n";
	}
	// std::cout << "\n";
	
#ifdef DEBUG
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			std::cout << prefixH[j][i];
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			std::cout << prefixV[j][i];
		}
		std::cout << "\n";
	}
	std::cout << "\n";
#endif

	while(!Q.empty()) {
		auto akt = Q.top(); Q.pop();	
		if(find(akt.second.first) == find(akt.second.second)) continue;		
		int a = pointToArray(akt.second.first.first, akt.second.first.second, N);
		int b = pointToArray(akt.second.second.first, akt.second.second.second, N);
		unionize(akt.second.first, akt.second.second);
		connections[a].push_back({b, akt.first});
		connections[b].push_back({a, akt.first});
		// std::cout << a << " " << b << " " << akt.first << "\n";
		// std::cout << akt.second.first.first << " " <<akt.second.first.second << " " <<
		// akt.second.second.first << " " << akt.second.second.second << " " << akt.first << "\n";
	}

#ifdef kjkjDEBUG
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
	
	int Q; std::cin >> Q;
	
	for(int i = 1; i <= N*N; ++i) {
		if(subtreeTable[i] == 0) {
			DFS(i);
			subtreeCounter++;
		}
	}
	
	// std::cout << "\n";
	// for(int i = 1; i <= N*N; ++i) {
	// 	std::cout << i << ": ";
	// 	for(int j = 0; j < 20; ++j)
	// 		std::cout << lcatable[i][j].first << " ";
	// 	std::cout << "\n";
	// }
	// std::cout << "\n";

	for(int i = 0; i < Q; ++i) {
		int a, b, c, d; std::cin >> b >> a >> d >> c;
		if(a == c and b == d) {
			std::cout << biggestSquare[a][b] << "\n";
			continue;
		}
		// std::cout << biggestSquare[a][b] << " " << biggestSquare[c][d] << "\n";
		int e = pointToArray(a, b, N), f = pointToArray(c, d, N);
		// std::cout << "\n" << e << " " << subtreeTable[e] << "\n";
		// std::cout << f << " " << subtreeTable[f] << "\n";
		if(subtreeTable[e] == subtreeTable[f] and (!table[a][b]) and (!table[c][d])) {
			std::cout << std::min(getLCABiggest(e, f), std::min(biggestSquare[a][b], biggestSquare[c][d])) << "\n";
			// std::cout << getLCAPoint(e, f) << "\n";
		}
		else std::cout << "0\n";
	}

}
