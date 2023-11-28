#include <ios>
#include <iostream>
#include <stack>
#include <vector>

const int MOD = 1e9+9; 

struct Node {
	std::vector<int> conn;
	int x = 0;
	int incoming = 0;
};

int N, M, A, B;
Node nodes[1000007];
std::stack<int> S;
std::vector<int> TS;

void Calculate() {
	while (!S.empty()) {
		int c = S.top(); S.pop();
		for(int x : nodes[c].conn) {
			nodes[x].incoming--;
			nodes[x].x = (nodes[x].x + nodes[c].x) % MOD;
			if(nodes[x].incoming == 0)
				S.push(x);
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(0); std::cin.tie(0);
	std::cin >> N >> M >> A >> B;

	for(int i = 0; i < M; ++i) {
		int a, b;
		std::cin >> a >> b;
		nodes[b].conn.push_back(a);
		nodes[a].incoming++;
	}

	for(int i = 1; i <= N; ++i) {
		if(nodes[i].incoming == 0)
			S.push(i);
	}
	nodes[B].x = 1;
	
	Calculate();
	std::cout << nodes[A].x;
}
