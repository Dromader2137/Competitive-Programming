#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> V[500007];
std::vector<int> VV[500007];
std::vector<std::pair<int,int>> P;
bool O[500007];
bool OS[500007];
int SSST[500007];

int PP = 1;
void DFS(int v) {
	O[v] = true;

	for(int x : V[v]) {
		if(O[x]) continue;
		DFS(x);
	}

	P.push_back({-PP, v});
	PP++;
}

int SSSI = 1;
void SSS(int v)
{
	OS[v] = true;
	SSST[v] = SSSI;
//	std::cout << v << " " << SSSI << "\n";

	for(int x : VV[v]) {
		if(OS[x]) continue;
		SSS(x);
	}
}

int main() {
	std::ios_base::sync_with_stdio(0); std::cin.tie(0);
	int N, M, Q; std::cin >> N >> M;

	for(int i = 0; i < M; ++i) {
		int a, b;
		std::cin >> a >> b;
		V[a].push_back(b);
		VV[b].push_back(a);
	}

	for(int i = 1; i <= N; ++i) {
		if(!O[i])
			DFS(i);
	}

	std::sort(P.begin(), P.end());
	
	//std::cout << "\n\n\n";
	for(auto i : P) {
		//std::cout << i.first << " " << i.second << "\n";
		if(!OS[i.second]) {
			SSS(i.second);
			SSSI++;
		}
	}

	std::cin >> Q;

	for(int i = 0; i < Q; ++i) {
		int a, b; std::cin >> a >> b;
		//std::cout << SSST[a] << " " << SSST[b] << "\n";
		if(SSST[a] == SSST[b]) std::cout << "Tak\n";
		else std::cout << "Nie\n";
	}	
}
