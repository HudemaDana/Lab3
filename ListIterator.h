#pragma once
#include "SortedIndexedList.h"


//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIndexedList;
private:
	SortedIndexedList& list;
	ListIterator(SortedIndexedList& list);

	int poz =-1;

public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
	TComp remove();
};


