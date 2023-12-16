/*
 *	Count articulation points from each vertex to vertex T
 */

#include <algorithm>
#include <iostream>
#include <vector>

#ifdef DEBUG
#define log(x) std::cout<<x<<std::endl
#else
#define log(x)
#endif

const int MAX_N = 2e5+7;

int N, M, T;
int low[MAX_N];
int height[MAX_N];
int articulation_points[MAX_N];
std::vector<int> connections[MAX_N];
std::vector<int> dfs_tree_connections[MAX_N];
bool visited[MAX_N];

int counter = 1;
void dfs_low(int v, int prev) {
	visited[v] = true;
	height[v] = counter;
	low[v] = counter++;
	for (int u : connections[v]) {
		if (u == prev) continue;
		if (visited[u]) {
			low[v] = std::min(low[v], height[u]);
		}
		else {
			dfs_tree_connections[v].push_back(u);
			dfs_low(u, v);
			low[v] = std::min(low[v], low[u]);
		}
	}
}

bool is_bridge(int v, int u) {
	return height[u] == low[u];
}

bool is_articulation_point(int v) {
	if(connections[v].size() < 2 or v == T) return false;

	bool is = (height[v] == low[v]);
	for (int u : dfs_tree_connections[v])
		is = (is or low[u] >= height[v]);

	return is;
}

void count_articulation_points(int v, int prev, bool bridge_ahead) {
	if(!is_articulation_point(v)) {
		for (int u : dfs_tree_connections[v]) {
			if (prev == u) continue;
			articulation_points[u] = articulation_points[v] + bridge_ahead;
			bool art_point = is_bridge(v, u);
			if (v != T) articulation_points[u] += art_point;
			count_articulation_points(u, v, art_point and (v != T));
		}
	}
	else {
		for (int u : dfs_tree_connections[v]) {
			if (prev == u) continue;
			articulation_points[u] = articulation_points[v] + (low[u] >= height[v]);
			count_articulation_points(u, v, false);
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);
	log("Runnig in Debug mode");
	std::cin >> N >> M >> T;
	
	for (int i = 0; i <= N; ++i)
		low[i] = -1;

	for (int i = 0; i < M; ++i) {
		int a, b; std::cin >> a >> b;
		connections[a].push_back(b);
		connections[b].push_back(a);
	}

	dfs_low(T, 0);
	count_articulation_points(T, 0, 0);

#ifdef DEBUG
	for (int i = 1; i <= N; ++i) {
		std::cout << height[i] << " ";	
	}
	std::cout << "\n";
	for (int i = 1; i <= N; ++i) {
		std::cout << low[i] << " ";	
	}
	std::cout << "\n";
	for (int i = 1; i <= N; ++i) {
		std::cout << is_articulation_point(i) << " ";	
	}
	std::cout << "\n";
#endif
	for (int i = 1; i <= N; ++i) {
		std::cout << articulation_points[i] << " ";	
	}
}
