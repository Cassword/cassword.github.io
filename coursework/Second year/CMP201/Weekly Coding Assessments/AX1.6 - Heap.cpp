
#include "Heap.h"
#include "time.h"
#include <vector>



// Recursive operation to arrange array to satisfy heap property focusing on the element at index i
void Heap::heapify(int i)
{
	int largest = i; //Position of the new value i 
	int left = 2 * i + 1; //Position of the left tree node
	int right = 2 * i + 2; // Position of the right tree node

	if (left <= last_index && arr[left]->hunger > arr[largest]->hunger) { //If we're not at the end and our new hunger is bigger than the largest hunger value
		largest = left;
	};
	if (right <= last_index && arr[right]->hunger > arr[largest]->hunger) { //if we're not at the end and our new hunger is bigger than our largest hunger value. 
		largest = right;
	};
	if (largest != i) { //if we're not at the largest is not the same as the new value then recursively heapify. 
		std::swap(arr[i], arr[largest]);
		heapify(largest);
	}

}

// Add a pointer to a bear object to the heap, heapify all internal nodes.
void Heap::push(Bear* c)
{
 	if (last_index == size - 1) {	//IF SIZE EXCEED, RESIZE THE ARRAY - GREAT 
		resize();
	}
	
	last_index++; 	//INCREMENT LASTINDEX TO ACCOMODATE NEW VALUE
	arr[last_index] = c; //VALUE OF LASTINDEX IS THE NEW VALUE - BECAUSE WE INSERT AT THE END
	for (int i = last_index / 2; i >= 0; i--) { // HEAPIFY THEM 
		heapify(i);
	}
	// assessed 1 mark
}

// Doubles the array referenced by the heap, copies values in element by element, updates reference.
void Heap::resize()
{
	// unassessed (look back to ArrayStacks and ArrayQueues, W4)
	size = size * 2;
	Bear** newArr = new Bear*[size]();
	for (int i = 0; i < last_index; i++) newArr[i] = arr[i];
	arr = newArr;
}

// Removes the element at the head of the heap, replaces with the final element, heapify all internal nodes
Bear* Heap::pop()
{
	Bear* root = arr[0];
	arr[0] = arr[last_index];
	arr[last_index] = NULL;
	last_index--;
	for (int i = last_index / 2; i>= 0; i--) {
		heapify(i);
	}

	return root;
}


std::vector<Bear*> Heap::toSortedVector()
{

	std::vector<Bear*> bears;
	for (int i = 0; i <= last_index; i++) {
		bears.push_back(arr[i]);
		heapify(i);
	}

	//This works, but it's not ideal. 
	for (int i = 0; i <= last_index; i++)
	{
		for (int j = i + 1; j <= last_index; j++)
		{
			if (bears[i]->hunger < bears[j]->hunger)
			{
				std::swap(bears[i], bears[j]);
			}
		}
	}


	return bears;
}

// Return a pointer to the hungriest bear
Bear* Heap::peek()
{
	return arr[0];
}

// Prints the name and hunger of a given bear.
void Bear::Check()
{
	// provided
	if (name != "")	std::cout << name << " is next, with a hunger of " << hunger << "\n";
}

// Return a pointer to a randomly generated bear with some prefix+suffix combination and a random hunger value from 1-200
Bear* Bear::randomBear()
{
	// provided
	std::string first_names[] = { "Grizzly", "Big", "Chubby", "Snoozy", "Dopey", "Hungry", "Ostentatious", "Territorial", "Fluffy", "Powerful", "Grumpy", "Whinny the", "Bewildered", "Rambunctious", "Uncouth", "Mischievous", "Baby", "Elderly", "Dapper"};
	std::string second_names[] = {"Alan", "Bella", "Charlie", "Danielle", "Evan", "Felicity", "Gerry", "Helena", "Iain", "Juliette", "Pooh"};
	std::string name = first_names[rand() % 19] + " " + second_names[rand() % 11];
	return new Bear(name, 1 + (rand() % 200));
}

