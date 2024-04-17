
#include "Sorting.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>		/* time */
#include <iostream>
#include <chrono>		/* timing */
#include <string>

void swap(int& a, int& b) { 
	int a_copy = a;
	a = b;
	b = a_copy;
}

// Bubble up and bubble back down.
// Runs in O(N^2).
void CocktailShakerSort(int a[], int size)
{
	for (int i = 0; i < (size / 2); i++) {//do half the list
		bool didSwap = false;
		for (int j = i; j < (size - 1 - i); j++) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
				didSwap = true;
			}
		}
		for (int j = (size - 2 - i); j > i; j--) {
			if (a[j] < a[j - 1]) {
				swap(a[j], a[j - 1]);
				didSwap = true;
				
			}
		}
		if (didSwap == false) {
			break;
		}
	}
}

// IN-PLACE implementation of insertion sort.
// Runs in O(N^2).
void InsertionSort(int a[], int size)
{
	for (int i = 1; i < size; i++) {
		int j = i;
		while (j > 0 && a[j - 1] > a[j]) {
			swap(a[j], a[j - 1]);
			j--;
		}
	}
}

int partition(int a[], int begin, int end)
{

	int pivot = a[end];
	int i = begin - 1;
	for (int j = begin; j <= (end - 1); j++) {
		if (a[j] < pivot) {
			i++;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1],a[end]);
	return i + 1;
}

// Sorting using partition() and recusion. Runs in O(n log(n))
void QuickSort(int a[], int begin, int end)
{
	if (begin < end) {
		int pi = partition(a, begin, end);
		QuickSort(a, begin, pi - 1);
		QuickSort(a, pi + 1, end);
	}

}

// Takes an array and it's size (as int), fills the array with random values from 1 to size*3
void fillArray(int a[], int size)
{
	for (int i = 0; i < size; i++)
	{
		a[i] = rand() % (size * 3);
	}
}

// Utility function: O(n) sorted check with early exit.
bool isSorted(int a[], int size)
{
	for (int i = 1; i < size; i++)
	{
		if (a[i] < a[i - 1]) return false;
	}
	return true;
}

// Utility function: Get two time points and return a string of nanoseconds between them.
std::string timeDelta(std::chrono::steady_clock::time_point t, std::chrono::steady_clock::time_point t2)
{
	long timeDelta = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t).count();
	return std::to_string(timeDelta) + " ns";
}

