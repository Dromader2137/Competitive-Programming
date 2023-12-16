#include <cstring>
#include <ios>
#include <iostream>
#include <vector>

constexpr int MAX_N = 1e5+7;
char current_color[MAX_N];
std::vector<int> connections_a[MAX_N];
std::vector<int> connections_b[MAX_N];
bool visited[MAX_N];

bool dfs(int v) {
	visited[v] = true;
	for (int x : connections_a[v]) {
		if (!visited[x]) {
			current_color[x] = current_color[v];
			dfs(x);
		} else if (current_color[v] != current_color[x]) {
			return false;
		}
	}
	for (int x : connections_b[v]) {
		if (!visited[x]) {
			current_color[x] = -current_color[v];
			dfs(x);
		} else if (current_color[v] == current_color[x]) {
			return false;
		}
	}
	return true;
}

bool handle_collection() {
	int n, m; std::cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		connections_a[i].clear();
		connections_b[i].clear();
		current_color[i] = 0;
	}
	std::memset(visited, 0, n + 1);

	for (int i = 0; i < m; ++i) {
		int a, b; char x; std::cin >> a >> b >> x;
		if (x == 'A') {
			connections_a[a].push_back(b);
			connections_a[b].push_back(a);
		} else {
			connections_b[a].push_back(b);
			connections_b[b].push_back(a);
		}
	}
	
	
	for (int i = 1; i <= n; ++i) {
		if (!visited[i]) {
			current_color[i] = 1;
			if (!dfs(i)) {
				return false;
			}
		}
	}

	return true;
}

int main() {
	std::ios_base::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);

	int t; std::cin >> t;
	
	for (int i = 0; i < t; ++i) {
		std::cout << (handle_collection() ? "TAK\n" : "NIE\n");
	}
}
