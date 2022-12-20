#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
void mergeSort(std::vector<long int>& s, size_t start, size_t end) {
	if (end - start < 2) {
		return;
	}
	if (end - start == 2) {
		if (s[start] > s[start + 1]) {
			std::swap(s[start], s[start + 1]);
		}
		return;
	}
	mergeSort(s, start, start + (end - start) / 2);
	mergeSort(s, start + (end - start) / 2, end);
	std::vector<long int> b;
	size_t bl = start;
	size_t el = start + (end - start) / 2;
	size_t b2 = el;
	while (b.size() < end - start) {
		if (bl >= el || (b2 < end && s[b2] <= s[bl])) {
			b.push_back(s[b2]);
			++b2;
		}
		else {
			b.push_back(s[bl]);
			++bl;
		}
	}
	for (size_t i = start; i < end; ++i) {
		s[i] = b[i - start];
	}
}
int main() {
	srand(time(0));
	std::vector<long int> s(10000000);
	for (int i = 0; i < 10000000; ++i) {
		s[i] = rand();
	}
	auto start = std::chrono::steady_clock::now();
	mergeSort(s, 0, s.size());
	auto end = std::chrono::steady_clock::now();
	std::cout << "Elapsed time in milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
}
