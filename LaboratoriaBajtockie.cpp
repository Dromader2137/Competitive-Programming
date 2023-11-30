#include <ios>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef DEBUG
#define log(x) std::cout<<x<<std::endl
#else
#define log(x)
#endif

const int MAX_N = 5e5+7;

std::vector<int> connections[MAX_N];
int dst[MAX_N];
int second_dst[MAX_N];
int previous[MAX_N];
int incoming[MAX_N];
std::unordered_set<int> main_road;
std::vector<int> main_road_ordered;

void first_dfs(int v, int prev) {
	dst[v] = dst[prev] + 1;
	log(v<<" "<<prev);
	for(int u : connections[v]) {
		if(u == prev) continue;
		first_dfs(u, v);
	}
}

void second_dfs(int v, int prev) {
	second_dst[v] = second_dst[prev] + 1;
	previous[v] = prev;
	log(v<<" "<<prev);
	for(int u : connections[v]) {
		if(u == prev) continue;
		incoming[v]++;
		second_dfs(u, v);
	}
}

void third_dfs(int v, int prev) {
	dst[v] = dst[prev] + 1;
	log(v<<" "<<prev);
	for(int u : connections[v]) {
		if(u == prev) continue;
		first_dfs(u, v);
	}
}

int main() { std::ios_base::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);
	int N; std::cin >> N;

	for(int i = 0; i < N - 1; ++i) { 
		int a, b; std::cin >> a >> b;
		connections[a].push_back(b);
		connections[b].push_back(a);
	}
	
	int farthest = 0, farthest_distance = -1;
	dst[0] = -1; second_dst[0] = -1;
	
	log("\nFirst DFS");
	first_dfs(1, 0);
	for(int i = 1; i <= N; ++i) {
		log(i<<": "<<dst[i]);
		if(farthest_distance < dst[i]) {
			farthest = i;
			farthest_distance = dst[i];
		}
	}
	
	log("\nSecond DFS");
	int second_farthest = farthest;
	second_dfs(second_farthest, 0);
	farthest_distance = -1;
	farthest = 0;
	for(int i = 1; i <= N; ++i) {
		log(i<<": "<<second_dst[i]);
		if(farthest_distance < second_dst[i]) {
			farthest = i;
			farthest_distance = second_dst[i];
		}
	}
	
	log("\nRoad Saving");
	int current = farthest;
	while(current != 0) {
		log(current);
		main_road.insert(current);
		main_road_ordered.push_back(current);
		current = previous[current];
	}

	std::queue<int> toposort_stack;
	for(int i = 1; i <= N; ++i) {
		if(main_road.find(i) == main_road.end() and incoming[i] == 0)
			toposort_stack.push(i);
	}

	log("\nThird DFS");
	third_dfs(farthest, 0);
	
	int64_t score = 0;
	std::vector<std::pair<int, int>> score_pairs;
	while (!toposort_stack.empty()) {
		int act = toposort_stack.front(); toposort_stack.pop();
		
		if (dst[act] > second_dst[act]) {
			score += dst[act];
			score_pairs.push_back({act, farthest});
		} 
		else {
			score += second_dst[act];
			score_pairs.push_back({act, second_farthest});
		}

		for(int u : connections[act]) {
			if(incoming[u] == 0) continue;
			incoming[u]--;
			if (incoming[u] == 0) toposort_stack.push(u);
		}
	}

	for(int i = main_road_ordered.size() - 1; i > 0; --i) {
		int it = main_road_ordered[i];
		score += dst[it];
		score_pairs.push_back({it, farthest});
	}

	std::cout << score << "\n";
	for(std::pair<int, int> x : score_pairs) std::cout << x.first << " " << x.second << "\n";
}
