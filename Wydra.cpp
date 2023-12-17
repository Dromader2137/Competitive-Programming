/*
 *
 *	In Progress - Don't use!!!
 *
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

struct Node {
	std::vector<int> connections;
	std::vector<int> reverse_connections;
	int sss_index = -1;
	bool visited;
};

struct SuperNode {
	std::vector<int> connections;
	int value = 0;
	int incoming = 0;
	int best = -1;
};

Node nodes[200007];
std::vector<SuperNode> super_nodes;
std::vector<std::pair<int, int>> postorders;
std::stack<int> stack;

int current_postorder = 1;
void dfs(int v) {
	nodes[v].visited = true;

	for(int x : nodes[v].connections) {
		if(!nodes[x].visited) dfs(x);
	}
	postorders.push_back({-current_postorder, v});
	current_postorder++;
}

int currentsss_index = 0;
void create_super_nodes(int v) {
	nodes[v].sss_index = currentsss_index;
	super_nodes[currentsss_index].value ++;

	for(int x : nodes[v].reverse_connections) {
		if(nodes[x].sss_index == -1) {
			create_super_nodes(x);
		}
		else if(nodes[x].sss_index != currentsss_index) {
			super_nodes[nodes[x].sss_index].connections.push_back(currentsss_index);
			super_nodes[currentsss_index].incoming++;
		}
	}
}

void calculate_score(int v) {
	super_nodes[v].best = super_nodes[v].value;
	if (super_nodes[v].best == 1) super_nodes[v].best = 0;
	
	int best_child = 0;
	for (int x : super_nodes[v].connections) {
		if (super_nodes[x].best == -1) {
			calculate_score(x);
		}
		best_child = std::max(best_child, super_nodes[x].best + 1);
	}
	super_nodes[v].best += best_child;
}

int read_int () {
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

int main() {
	std::ios_base::sync_with_stdio(0); std::cin.tie(0);
	int n = read_int(), m = read_int();

	for(int i = 1; i <= m; ++i) {
		int a = read_int(), b = read_int();
		nodes[a].connections.push_back(b);
		nodes[b].reverse_connections.push_back(a);
	}

	for(int i = 1; i <= n; ++i) {
		if(nodes[i].visited) continue;
		dfs(i);
	}

	std::sort(postorders.begin(), postorders.end());
	
	for(auto x : postorders) {
		int current = x.second;
		if(nodes[current].sss_index == -1) {
			super_nodes.push_back(SuperNode());
			create_super_nodes(current);
			currentsss_index++;
		}
	}

	for (int i = 0; i < super_nodes.size(); ++i) {
		if (super_nodes[i].best == -1) {
			calculate_score(i);
		}
	}

	for (int i = 1; i <= n; ++i) {
		std::cout << super_nodes[nodes[i].sss_index].best << "\n";
	}
}
