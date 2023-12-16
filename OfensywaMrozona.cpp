#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#ifdef DEBUG
#define log(x) std::cout<<x<<std::endl
#else
#define log(x)
#endif

constexpr int MAX_N = 5e5+7;
constexpr int BASE = 1<<20;

struct Path {
	int a, b;
	int cutoff, weight;
};

struct Query {
	int a, b;
	int weight;
	int id;
};

bool path_cmp(const Path& a, const Path& b) {
	return a.cutoff < b.cutoff;
}

bool query_cmp(const Query& a, const Query& b) {
	return a.weight < b.weight;
}

int64_t tree_sum[BASE * 2];
int distance_from_root[MAX_N];
int preorder[MAX_N];
int postorder[MAX_N];
int lca_table[MAX_N][20];
std::vector<int> connections[MAX_N];
std::vector<Path> paths;
std::vector<Query> queries;

void tree_add(int a, int b, int64_t v) {
	a += BASE - 1;
	b += BASE + 1;
	while (a / 2 != b / 2) {
		log(a<<" "<<b);
		if (a % 2 == 0) tree_sum[a + 1] += v;
		if (b % 2 == 1) tree_sum[b - 1] += v;
		a /= 2;
		b /= 2;
	}
	log("---");
}

int64_t tree_get(int x) {
	log("--");
	log(x);
	x += BASE;
	int64_t score = tree_sum[x];
	log(x);
	x /= 2;
	while (x > 0) {
		log(x<<" "<<score);
		score += tree_sum[x];
		x /= 2;
	}
	log(score);
	return score;
	log("--");
}

bool subtree(int a, int b) {
	return preorder[a] <= preorder[b] and postorder[a] >= postorder[b];
}

void calculate_lca(int v, int prev) {
	lca_table[v][0] = prev;
	for (int i = 0; i < 19; ++i) {
		lca_table[v][i + 1] = lca_table[lca_table[v][i]][i];
		if (lca_table[v][i + 1] == 0) break;
	}
}

int timer = 1;
void calculate_distance_order_lca(int v, int prev) {
	preorder[v] = timer++;
	distance_from_root[v] = distance_from_root[prev] + 1;
	for (int x : connections[v]) {
		if (x == prev) continue;
		calculate_lca(x, v);
		calculate_distance_order_lca(x, v);
	}
	postorder[v] = timer++;
}

int get_lca(int a, int b) {
	if (subtree(a, b)) return a;
	if (subtree(b, a)) return b;

	for (int i = 19; i >= 0; --i) {
		if (lca_table[a][i] == 0) continue;
		if (!subtree(lca_table[a][i], b)) a = lca_table[a][i];
	}	

	return lca_table[a][0];
}

int main() {
#ifndef DEBUG
	std::ios_base::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);
#endif
	int n, q; std::cin >> n >> q;

	log("1");

	for (int i = 0; i < n - 1; ++i) {
		int a, b, cutoff, weight; std::cin >> a >> b >> cutoff >> weight;
		connections[a].push_back(b);
		connections[b].push_back(a);
		paths.push_back({a, b, cutoff, weight});
	}

	log("2");

	for (int i = 0; i < q; ++i) {
		int a, b, weight; std::cin >> a >> b >> weight;
		queries.push_back({a, b, weight, i});
	}

	log("3");

	std::sort(paths.begin(), paths.end(), path_cmp);
	std::sort(queries.begin(), queries.end(), query_cmp);

	log("4");

	distance_from_root[0] = -1;
	calculate_distance_order_lca(1, 0);
	for (int i = 0; i < n - 1; ++i) {
		if (distance_from_root[paths[i].a] > distance_from_root[paths[i].b]) {
			std::swap(paths[i].a, paths[i].b);
		}
	}

	log("5");

	int path_iterator = 0;
	int64_t results[q]; 
	for (int i = 0; i < q; ++i) {
		log(queries[i].a<<" "<<queries[i].b<<" "<<queries[i].weight);
		while (queries[i].weight >= paths[path_iterator].cutoff and path_iterator < paths.size()) {
			tree_add(preorder[paths[path_iterator].b], postorder[paths[path_iterator].b], paths[path_iterator].weight);
			path_iterator++;
		}
		
		int a = queries[i].a;
		int b = queries[i].b;
		int c = get_lca(a, b);
		log(a<<" "<<b<<" "<<c);

		results[queries[i].id] = tree_get(preorder[a]) + tree_get(preorder[b]) - 2 * tree_get(preorder[c]);
		log("-----");
	}

	for (int i = 0; i < q; ++i) std::cout << results[i] << "\n"; 
}
