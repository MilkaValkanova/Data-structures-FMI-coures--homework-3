/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Milka Valkanova
* @idnumber 45155
* @task 1
* @compiler VC
*
*/

#pragma once
#include "RadixTree.h"
#include <fstream>
class Dictionary
{
private:
	Trie dictionary;

public:
	Dictionary(const char*);
	void search(const char*)const;
	inline void print() const{ dictionary.print(); }
};
