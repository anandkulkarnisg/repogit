#include<iostream>
#include<string>
#include <map>
#include <iterator>
#include <algorithm>
 
int main()
{
	//MultiMap of char and int
	std::multimap<char, int> mmapOfPos =
	{
		{'a', 1},
		{'b', 2},
		{'c', 3},
		{'a', 4},
		{'c', 5},
		{'c', 6},
		{'d', 7},
	};
 
	typedef std::multimap<char, int>::iterator MMAPIterator;
 
	// It returns a pair representing the range of elements with key equal to 'c'
	std::pair<MMAPIterator, MMAPIterator> result = mmapOfPos.equal_range('c');
 
	std::cout << "All values for key 'c' are," << std::endl;
 
	// Iterate over the range
	for (MMAPIterator it = result.first; it != result.second; it++)
		std::cout << it->second << std::endl;
 
	// Total Elements in the range
	int count = std::distance(result.first, result.second);
	std::cout << "Total values for key 'c' are : " << count << std::endl;
 
	return 0;
}
