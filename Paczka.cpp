#include <algorithm>
#include <ios>
#include <iostream>
#include <vector>

constexpr int MAX_A = 1e3;

bool same_parity(int a, int b) {
	return (a + MAX_A) % 2 == (b + MAX_A) % 2;
}

int handle_case() {
	int n; std::cin >> n;
	int prev = 0;
	int curr; std::cin >> curr;
	int max_score = curr;
	int min_in_subsequence = std::min(0, curr);
	int current_prefix_sum = curr;

	for (int i = 1; i < n; ++i) {
		prev = curr;
		std::cin >> curr;
		
		if (same_parity(prev, curr)) {
			min_in_subsequence = std::min(0, curr);
			max_score = std::max(max_score, curr);
			current_prefix_sum = curr;
		} else {
			current_prefix_sum += curr;
			max_score = std::max(max_score, current_prefix_sum - min_in_subsequence);
			min_in_subsequence = std::min(min_in_subsequence, current_prefix_sum);
		}
	}

	return max_score;
}

int main() {
	std::ios_base::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);

	int t; std::cin >> t;

	for (int i = 0; i < t; ++i) {
		std::cout << handle_case() << "\n";
	}
}
