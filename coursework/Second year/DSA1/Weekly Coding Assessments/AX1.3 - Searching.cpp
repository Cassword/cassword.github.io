#include "Search.h"
#include <vector>
#include <stdlib.h>		// for RNG
#include <time.h>		// for RNG
#include <iostream>
#include <chrono>		// for timing
#include <map>


// Return index position of key in arr or -1 if not in collection.
// Search using a naive scan.
int LinearScan(std::vector<int> arr, int key)
{
	int i = 0;
	while (i < arr.size())
		if (arr[i] == key) {
			return i;
		}
		else { i++; }
	return -1;
}
// Return index position of key in arr or -1 if not in collection.
// Search using binary reduction
int BinarySearch(std::vector<int> arr, int key)
{
	int high = arr.size() - 1;
	int low = 0;
	while (low <= high) {
		int mid = floor((high + low) / 2);
		if (arr[mid] == key){
			return mid;
		}
		else if (arr[mid] < key) {
			low = mid + 1;
		}
		else { high = mid - 1; }
	}
	return -1;
}

// Return index position of key in arr or -1 if not in collection.
// Search using interpolation guestimates.
int InterpolationSearch(std::vector<int> arr, int key)
{
	int start = 0;
	int end = arr.size() - 1;
	while (start <= end && key >= arr[start] && key <= arr[end]) { //Do we need all these? Maybe not, we could probably get rid of start<=end but I don't think they cause any issues so I'll leave them alone.  
		float dist = key - arr[start];
		float valRange = arr[end] - arr[start];
		float fraction = dist / valRange; // make dist and valrange a float, because it's the easier of the many ways we could use to mean it won't get angry about truncation. 
		int indexRange = end - start;
		int estimate = start + (fraction * indexRange);
		if (arr[estimate] == key){
			return estimate;
		}
		else if (arr[estimate] < key) {
			start = estimate + 1;
		}
		else { end = estimate - 1; }
	}
	return -1;
}

/*
Generate a vector of length <size> where each element is
1-5 larger than the previous element.
*/
std::vector<int> SortedVectorGenerator(int size)
{
	std::vector<int> v = std::vector<int>();
	srand(time(NULL));
	int last_value = 0;
	for (int i = 0; i < size; i++)
	{
		int new_value = last_value + rand() % 5 + 1;
		v.push_back(new_value);
		last_value = new_value;
	}
	return v;
}

// Runs the three searches on the three vectors with the three targets supplied as parameters.
// i.e. LS(v0, t0), BS(v0, t0), IS(v0, t0), LS(v1, t1), ... etc.
// Returns a map of search name to vector of doubles with timing results in nanoseconds.
// Example map output:
//		"binary search":{13400, 6400, 238100}
//		"interpolation search":{2500, 303800, 237100}
//		"linear scan":{2200, 59700, 1.4251e+06}
std::map<std::string, std::vector<double>> 
runTests(std::vector<int> v0, std::vector<int> v1, std::vector<int> v2,
	int t0, int t1, int t2)
{
	std::map<std::string, std::vector<double>> myMap;
	std::vector<int> vectorList[3] = { v0,v1,v2 }; //make array of vectors so it's easier to iterate through the vectors
	int targetList[3] = { t0,t1,t2 }; //make an array of targets
	std::vector<double> binaryVector; //make the vectors for our map 
	std::vector<double> interpolVector;
	std::vector<double> linearVector;

	for (int i = 0; i < 3; i++) {

		auto start = std::chrono::high_resolution_clock::now();
		BinarySearch(vectorList[i], targetList[i]);
		auto end = std::chrono::high_resolution_clock::now();
		long timeDelta = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		binaryVector.push_back(timeDelta);
	}
	for (int i = 0; i < 3; i++) {

		auto start = std::chrono::high_resolution_clock::now();
		InterpolationSearch(vectorList[i], targetList[i]);
		auto end = std::chrono::high_resolution_clock::now();
		long timeDelta = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		interpolVector.push_back(timeDelta);
	}
	for (int i = 0; i < 3; i++) {
		auto start = std::chrono::high_resolution_clock::now(); //start
		LinearScan(vectorList[i], targetList[i]); //run function
		auto end = std::chrono::high_resolution_clock::now(); //stop
		long timeDelta = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		linearVector.push_back(timeDelta);
	}
	
	myMap["binary search"] = binaryVector;
	myMap["interpolation search"] = interpolVector; 
	myMap["linear scan"] = linearVector; 


	return myMap;
	
}




