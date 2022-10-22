#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>
#include<utility>


//Theta(1)
SortedIndexedList::SortedIndexedList(Relation r) {
	this->cap = 5;
	arr = new DLLANode[cap];
	this->firstFree = 0;
	this->head = -1;
	this->tail = -1;
	this->rel = r;

}

//Theta(1)
int SortedIndexedList::size() const {

	return size_arr;
}

//Theta(1)
bool SortedIndexedList::isEmpty() const {
	if (size_arr==0)
		return true;
	return false;
}

//Theta(1)
TComp SortedIndexedList::getElement(int i) const{
	if (i < 0 || i >= firstFree)
		throw exception();
	return arr[i].elem;
}

//Theta(1)
TComp SortedIndexedList::remove(int i) {
	if (i <0 || i>=firstFree )
		throw exception();

	TComp nr;
	if (i == tail)
	{
		arr[arr[i].prev].next = -1;
		tail = arr[i].prev;
		nr = arr[i].elem;
	}
	else if (i == head)
	{
		arr[arr[i].next].prev = -1;
		head = arr[i].next;
		nr = arr[i].elem;
		arr[i].elem = arr[arr[i].next].elem;
		arr[i].next = arr[arr[i].next].next;
	}
	else
	{	
 
		arr[arr[i].next].prev = arr[i].prev;
		arr[arr[i].prev].next = arr[i].next;
		nr = arr[i].elem;
		arr[i].elem = arr[arr[i].next].elem;
		arr[i].next = arr[arr[i].next].next;

	}
	
	size_arr--;
	return nr;
}


//WC: O(n), BC: Omega(1), AC: O(n) => total: O(n)
int SortedIndexedList::search(TComp e) const {
	int poz = head;

	if (size_arr == 0)
		return -1;

	while (poz != tail && this->rel(arr[poz].elem, e) == true && arr[poz].elem!=e)
		poz = arr[poz].next;
	if (arr[poz].elem == e)
		return poz;
	if (poz == tail && arr[poz].elem == e)
		return poz;
	else if (poz == head)
	{
		if (this->rel(arr[poz].elem, e) == false)
			return -1;
		else if(arr[poz].elem== e)
			return poz;
	}
	else if (arr[arr[poz].prev].elem == e)
		return arr[poz].prev;
	return -1;
}

//WC:O(n), BC: Omega(1), AC: O(n) => total O(n)
void SortedIndexedList::add(TComp e) {	
	
	if (size_arr == cap)
	{
		cap *= 2;
		DLLANode* copy = new DLLANode[cap];
		for (int i = 0; i < firstFree; i++)
			copy[i] = arr[i];
		
		
		delete[] arr;
		arr = copy;
	}
	if (size_arr == 0)
		firstFree = 0;

	int poz = head;

	while (poz != -1 && this->rel(arr[poz].elem, e) == true)
		poz = arr[poz].next;

	//add end
	if (poz == -1)
	{
		arr[firstFree].next = -1;
		arr[firstFree].prev = tail;
		arr[firstFree].elem = e;
		if (head != -1)
		{
			arr[tail].next = firstFree;
			tail = firstFree;
		}
		else
		{
			head = firstFree;
			tail = firstFree;
		}

	}//add beggining
	else if (poz==head)
	{
		
			arr[firstFree].elem = e;
			arr[firstFree].prev = -1;
			arr[firstFree].next = head;
			arr[head].prev = firstFree;
			head = firstFree;

	}//add middle
	else
	{
		int nr = arr[poz].prev;
		arr[firstFree].prev = nr;
		arr[firstFree].next = poz;
		arr[firstFree].elem = e;
		arr[nr].next = firstFree;
		arr[poz].prev = firstFree;
	}
	
	firstFree++;
	size_arr++;
}

//Theta(1)
ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//Theta(1)
SortedIndexedList::~SortedIndexedList() {
	delete[] arr;
}
