
#include "LinkedList.h"
#include <iostream>

// default Constructor
template <class T>
LinkedList<T>::LinkedList()
{
	LinkedList::head = nullptr;
}

// Single element constructor set head to new Node(n)
template<class T>
LinkedList<T>::LinkedList(T n)
{
	head = new Node<T>(n);
	head->next = head;
	head->prev = head;
}

template<class T>
LinkedList<T>::~LinkedList()
{
}

// Insertion, append to LL, update references.
template<class T>
void LinkedList<T>::Insert(T n)
{
	if (!head)
	{
		head = new Node<T>(n); //Because list is empty 
		head->next = head;
		head->prev = head;
		return;
	}
	Node<T>* tail = head->prev; //pointer to tail
	tail->next = new Node<T>(n); //append node to the end, make it the next thing the tail is pointing at. 
	head->prev = tail->next; //Make the position before the head point to our new node 
	head->prev->next = head; //make the new node's next point to the head 
	tail->next->prev = tail; // make the new node's previous point to the tail
}

// Removal, delete first element found matching param, update references
template<class T>
void LinkedList<T>::Remove(T n)
{
	if (head->data == n) {
		if (head->prev == head) { //if this is true, it's cicularly looping back to the head - so only has the one thing in the list
			head = NULL; //delete the head, leaving us with nothing. 
			return; //we're done here, because there is nothing left. 
		}
		else {
			Node<T>* newHead = head->next; //make a pointer to head and tail
			Node<T>* tail = head->prev;
			newHead->prev = tail; //set the previous location of our new head to the tail
			tail->next = newHead; //set the next location of our tail to where the new head value will be
			head = newHead; //set the head to the new head. 
			return;
		};
	}
	Node<T>* temp = head;
	while (temp->next) { //iterate through whole list
		if (temp->next->data == n) { //check if value is equal to n
			temp->next = temp->next->next; //set next to the node after the detected value. "Skip" the node.
			temp->next->prev = temp;
			return;
		}
		else { temp = temp->next; } //if it's not n, keep iterating
	}
}

// Return element at position indexed by param <index>
template<class T>
Node<T>* LinkedList<T>::Get(int index)
{
	if (index == 0) return head;
	Node<T>* temp = head;
	for (int i = 0; i < index; i++)
	{
		temp = temp->next;
	}
	return temp;
}


// Flip the order of all elements in the LL such that head becomes the tail.
template<class T>
void LinkedList<T>::Reverse()
{
	if (head) {
		Node<T>* temp = head;
		Node<T>* prevNode = head; 
		Node<T>* currNode = head->next;

		prevNode->next = prevNode;
		prevNode->prev = prevNode;
		while (currNode != head) { //Repeat for as long as our current node is not equal to head, when it is the list will have fully reversed as former head will be the new tail.
			temp = currNode->next; //ensure temp is always the node after current
			prevNode->prev = currNode; //swap the references. Make the previous point to the next node, and the next point to the previous because we're reversing it. 
			currNode->next = prevNode;
			head->next = currNode; // update head.next as we move through the list 
			currNode->prev = head; //ensure currNode.prev is always our former head, aka our new tail - because when we've fully reversed we want it to point back there. 

			prevNode = currNode; //make prevNode = currNode before we change currNode
			currNode = temp; //Temp is value after our current node, If reversal was successful then the cur should now be equal the head, creating the exit conditon for our loop

			//head is still pointing to the last node, so we've got to change that. 
		}
		head = prevNode; //make the prevNode into the new head
	}
}

// return count of elements in LL
template<class T>
int LinkedList<T>::Size()
{
	if (!head) return 0;
	Node<T>* temp = head;
	int count = 1;
	while (temp->next != head)
	{
		temp = temp->next;
		count++;
	}
	return count;
}

// Convert all elements into a vector 
template<class T>
std::vector<T> LinkedList<T>::ToVector()
{
	std::vector<T> returnVector;
	if (!head) return returnVector;
	Node<T>* temp = head;
	for (int i = 0; i < Size(); i++)
	{
		returnVector[i] = temp->data;
		temp = temp->next;
	}
	return returnVector;
}

// Return pointer to the tail 
template<class T>
Node<T>* LinkedList<T>::GetTail()
{
	if (!head) return nullptr;
	return head->prev;
}


// A generic toString (numeric types typically)
template<class T>
std::string LinkedList<T>::ToString()
{
	std::string returnString = "[";
	Node<T>* t = head;
	while (t)
	{
		returnString += std::to_string(t->data);
		// comma if there is more to come.
		if (t->next != head)
		{
			returnString += ", ";
		}
		else
		{
			break;	// we're done, leave.
		}
		t = t->next;
	}
	return returnString + "]\n";	// end and newline.
}

// specific toString for ll<std::string> 
template <>
std::string LinkedList<std::string>::ToString()
{
	std::string returnString = "[";
	Node<std::string>* t = head;
	while (t)
	{
		returnString += t->data;

		// comma if there is more to come.
		if (t->next != head)
		{
			returnString += ", ";
		}
		else
		{
			break;	// we're done, leave.
		}
		t = t->next;
	}
	return returnString + "]\n";	// end and newline.
}

// specific toString for ll<char> 
template <>
std::string LinkedList<char>::ToString()
{
	std::string returnString = "[";
	Node<char>* t = head;
	while (t)
	{
		returnString += t->data;

		// comma if there is more to come.
		if (t->next != head)
		{
			returnString += ", ";
		}
		else
		{
			break;	// we're done, leave.
		}
		t = t->next;
	}
	return returnString + "]\n";	// end and newline.
}

