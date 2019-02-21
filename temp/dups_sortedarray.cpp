#include<iostream>
#include<vector>
#include<set>

using namespace std;

set<int> solution(const vector<int>& V)
{

	std::size_t size = V.size();
	set<int> results;

	for(unsigned int i=0; i<size-1; ++i)
	{
		if(V[i+1] == V[i])
			results.insert(V[i]);
	}

	return(results);
}

bool isAnyDuplicate(const vector<int>& V)
{

	std::size_t size = V.size();

	if(size == 1)
		return(false);

	std::size_t SIZE = V[V.size()-1];
	int arr[SIZE] = { 0 };

	for(unsigned int i=0; i<size; ++i)
	{
		arr[V[i]] +=1;
		if(arr[V[i]] > 1)
			return(true);
	}		

	return(false);
}



int main(int argc, char* argv[])
{
	vector<int> A = { 1, 2, 2, 3, 4, 4, 4, 5, 6, 6, 7 };
	set<int> result = solution(A);
	for(auto iter : result)
		cout << iter;
	cout << "duplicate status = " << isAnyDuplicate(A) << endl;

	vector<int> B = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 99 };
	cout << "duplicate status = " << isAnyDuplicate(B) << endl;	

	vector<int> C = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 9 };
	cout << "duplicate status = " << isAnyDuplicate(C) << endl;

}
