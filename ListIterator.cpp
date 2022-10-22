#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

//Theta(1)
ListIterator::ListIterator(SortedIndexedList& list) : list(list) {
	if (list.head >= 0)
		poz = list.head;
	else
		poz = -1;
}

//Theta(1)
void ListIterator::first(){
	if(list.head>=0)
		poz = list.head;
	else
		poz = -1;
}

//Theta(1)
void ListIterator::next(){
	if (poz==-1)
		throw exception();
	else
		poz = list.arr[poz].next;
}

//Theta(1)
bool ListIterator::valid() const{
	if (poz==-1)
		return false;
	return true;
}

//Theta(1)
TComp ListIterator::getCurrent() const{
	if(this->valid())
		return list.arr[poz].elem;
	throw exception();
}

//Theta(1)
TComp ListIterator::remove()
{
	if (!valid())
		throw exception();

	int next_poz = list.arr[poz].next;
	TComp nr = list.remove(poz);
	poz = next_poz;

	return nr;
}


