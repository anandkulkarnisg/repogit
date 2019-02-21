#include<iostream>
#include<vector>
#include<string>
#include<deque>
#include<algorithm>

using namespace std;

int main(int argc, char* argv[])
{
	int array[] = { 1,2,3,4,5 };
	std::deque<int> m_deque;
	for(unsigned int i=0; i<5;++i)
		m_deque.push_back(array[i]);

	std::sort(m_deque.begin(), m_deque.end());
	auto iter = std::find(m_deque.begin(), m_deque.end(), 3);
	if(iter != m_deque.end())
	{
		std::cout << (iter-m_deque.begin()) << std::endl;
		*iter = 10;
	}
	else
	{
		std::cout << "not found!" << std::endl;	
	}
	
	for(const auto& iter : m_deque)
		std::cout << iter << std::endl;
	
	return(0);
}
