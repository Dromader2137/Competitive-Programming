#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

struct Node {
	std::vector<int> connections;
	std::vector<int> reverseConnections;
	int value;
	int sssindex = -1;
	bool visited;
};

struct SuperNode {
	std::vector<int> connections;
	std::vector<int> reverseConnections;
	int value = 0;
	int incoming = 0;
	int best;
};

Node nodes[200007];
std::vector<SuperNode> superNodes;
std::vector<std::pair<int, int>> postorders;
std::stack<int> stack;

int currentPostorder = 1;
void DFS(int v) {
	nodes[v].visited = true;

	for(int x : nodes[v].connections) {
		if(!nodes[x].visited) DFS(x);
	}
	postorders.push_back({-currentPostorder, v});
	currentPostorder++;
}

int currentsssindex = 0;
void CreateSuperNodes(int v) {
	nodes[v].sssindex = currentsssindex;
	superNodes[currentsssindex].value += nodes[v].value;

	for(int x : nodes[v].reverseConnections) {
		// std::cout << v << " " << x << "\n";
		if(nodes[x].sssindex == -1) {
			CreateSuperNodes(x);
		}
		else if(nodes[x].sssindex != currentsssindex) {
			superNodes[nodes[x].sssindex].connections.push_back(currentsssindex);
			superNodes[currentsssindex].reverseConnections.push_back(nodes[x].sssindex);
			superNodes[currentsssindex].incoming++;
		}
	}
}

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

int main() {
	std::ios_base::sync_with_stdio(0); std::cin.tie(0);
	int N = readInt(), M = readInt();

	for(int i = 1; i <= N; ++i) {
		int a = readInt();
		nodes[i].value = a;
	}

	for(int i = 1; i <= M; ++i) {
		int a = readInt(), b = readInt();
		nodes[a].connections.push_back(b);
		nodes[b].reverseConnections.push_back(a);
	}

	for(int i = 1; i <= N; ++i) {
		if(nodes[i].visited) continue;
		DFS(i);
	}

	std::sort(postorders.begin(), postorders.end());
	
	// std::cout << "\n";
	for(auto x : postorders) {
		// std::cout << -x.first << " => " << x.second << "\n";
		int current = x.second;
		if(nodes[current].sssindex == -1) {
			superNodes.push_back(SuperNode());
			CreateSuperNodes(current);
			currentsssindex++;
		}
	}

	// for (int i = 1; i <= N; ++i) {
	// 	std::cout << i << " -> " << nodes[i].sssindex << "\n";
	// }
	
	// std::cout << superNodes.size() << "\n";
	for(int i = 0; i < superNodes.size(); ++i) {
		// std::cout << i << " = " << superNodes[i].incoming << "\n";
		// for(int x : superNodes[i].connections)
			// std::cout << i << " -- " << x << "\n";
		if(superNodes[i].incoming == 0)
			stack.push(i);
	}

	int result = 0;
	while (!stack.empty()) {
		int current = stack.top(); stack.pop();
		superNodes[current].best = superNodes[current].value;
		int max = 0;
		for(int x : superNodes[current].reverseConnections)
			max = std::max(max, superNodes[x].best);

		for(int x : superNodes[current].connections) {
			superNodes[x].incoming--;	
			if (superNodes[x].incoming == 0) {
				stack.push(x);
			}
		}
		superNodes[current].best += max;
		result = std::max(result, superNodes[current].best);
		// std::cout << current << " " << superNodes[current].best << " " << superNodes[current].value << "\n";
	}

	std::cout << result;
}
