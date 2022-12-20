#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <algorithm>
using namespace std;
void outVector(std::vector<long int>& s, int n) //Вывод вектора (Если нужно)
{
	for (int i = 0; i < n; ++i) {
				cout << s[i] << endl; 
			}
}
void mergeSort(std::vector<long int>& s, size_t start, size_t end) { //Сортировка слиянием (Илья)
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

void heapify(vector <long int> &arr, int n, int i) // функция для пирамидальной
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && arr[l] > arr[largest])
		largest = l;
	if (r < n && arr[r] > arr[largest])
		largest = r;
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}

void heapsort(vector <long int> arr, int n) //Пирамидальная (Влад)
{
		for (int i = n / 2 - 1; i >= 0; i--)
			heapify(arr, n, i);
		for (int i = n - 1; i >= 0; i--)
		{
			swap(arr[0], arr[i]);
			heapify(arr, i, 0);
		}
}

int main() {
	int t = 1000; // Количество тестов
	cout << "MergeSort HeapSort ...other" << endl; //Названия писать сюда
	while (--t)
	{
		srand(time(0));
		int n = 10000000; // Количество элементов
		std::vector<long int> s(n);
		for (int i = 0; i < n; ++i) {
			s[i] = rand();
		}

		auto start = std::chrono::steady_clock::now();
		mergeSort(s, 0, s.size()); //Сортировка слиянием (Илья)
		auto end = std::chrono::steady_clock::now();

		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << "      ";

		//outVector(s, n); //Вывод вектора (Если нужно)

		for (int i = 0; i < n; ++i) {
			s[i] = rand(); //Переопределение вектора рандомными числами
		}

		start = std::chrono::steady_clock::now();
		heapsort(s, n); //Пирамидальная (Влад)
		end = std::chrono::steady_clock::now();

		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << "      ";
		cout << endl;
	}
}
