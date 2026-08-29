#include <iostream>
#include "EHDataStructure.h"

int main()
{
	eh::list<int> l;
	for (int i = 0; i < 10; ++i)
		l.emplaceback(i);
	l.insert(0, 100);
	for (int i = 0; i < 11; ++i)
		std::cout << l[i] << std::endl;
}