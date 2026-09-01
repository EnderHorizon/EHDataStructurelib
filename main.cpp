#include <iostream>
#include "EHDataStructure.h"

int main()
{
	eh::string s("Hello");
	eh::string n("World");
	std::cout << s << std::endl;
	std::cout << n << std::endl;
	std::cout << s+n << std::endl;
}