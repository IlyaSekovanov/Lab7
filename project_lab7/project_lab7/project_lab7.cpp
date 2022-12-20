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
} //сортировка слиянием

void heapify(vector <long int>& arr, int n, int i) // функция для пирамидальной
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

void vstavka(std::vector<long int>& s, int size) // сортировка вставками (Саша)
{
	long int indexlast, element, j, i;
	for (i = 1; i < size; i++)
	{
		element = s[i];
		indexlast = i - 1;
		for (j = indexlast; j >= 0 && element < s[j]; j--)
		{
			s[j + 1] = s[j];
		}
		s[j + 1] = element;
	}
}

void shell(vector <long int> &arr, long long int N)  //Шелла (Никита Бархатов)
{
	for (long long int d = N / 2; d > 0; d /= 2)
	{
		for (long long int i = d; i < N; i++)
		{
			long long int el = arr[i];
			long long int j;
			for (j = i; j >= d && arr[j - d] > el; j -= d)
				arr[j] = arr[j - d];
			arr[j] = el;
		}
	}
}

void qsort(vector<long int> &s, int size) { //быстрая сортировка (Никита Литовкин)
	int i = 0;
	int j = size - 1;
	int mid = s[size / 2];
	do {
		while (s[i] < mid) {
			i++;
		}
		while (s[j] > mid) {
			j--;
		}
		if (i <= j) {
			int tmp = s[i]; s[i] = s[j]; s[j] = tmp;
			i++;
			j--;
		}
	} while (i <= j);
	if (j > 0) {
		qsort(s, j + 1);
	}
	if (i < size) {
		qsort(s, size - i);
	}
}

int main() {
	int t = 1000; // Количество тестов
	cout << "MergeSort   HeapSort   InsertionSort   ShellSort   QuickSort" << endl; //Названия писать сюда
	while (--t)
	{
		srand(time(0));
		int n = 10000000; // Количество элементов
		int k = 10000; // кол-во элементов для сортировки вставками
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
		heapsort(s, n); //Пирамидальная Влад
		end = std::chrono::steady_clock::now();

		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << "      ";

		std::vector<long int> v(k); //вектор для сортировки вставками
		for (long long int i = 0; i < k; i++) {
			v[i] = rand();
		}
		start = std::chrono::steady_clock::now();
		vstavka(v, k); // Вызов сортировки вставками
		end = std::chrono::steady_clock::now();

		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << "      ";

		for (int i = 0; i < n; ++i) {
			s[i] = rand(); //Переопределение вектора рандомными числами
		}

		start = std::chrono::steady_clock::now();
		shell(s, n); //Шелла (Никита Бархатов)
		end = std::chrono::steady_clock::now();

		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << "      ";

		for (int i = 0; i < n; ++i) {
			s[i] = rand(); //Переопределение вектора рандомными числами
		}

		start = std::chrono::steady_clock::now();
		qsort(s, n); // Быстрая сортировка Никита Литовкин
		end = std::chrono::steady_clock::now();

		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << "      " << std::endl;
	}
}
