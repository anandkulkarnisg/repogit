#include<iostream>
#include<string>
#include<vector>

using namespace std;

void mergeArrays(vector<int>& vec1, const vector<int>& vec2)
{
	// We are already sure that both vectors in themselves are sorted.
	int leftArraySize = vec1.size();
	int rightArraySize = vec2.size();

	int leftArray[leftArraySize];
	int rightArray[rightArraySize];

	for(int i=0; i<leftArraySize; ++i)    
		leftArray[i]=vec1[i];

	for(int j=0; j<rightArraySize; ++j)
		rightArray[j]=vec2[j];

	int i=0, j=0, k=0;

	while(i<leftArraySize && j<rightArraySize)
	{
		if(leftArray[i] <=  rightArray[j])
		{
			vec1[k] = leftArray[i]; 
			++k; ++i;   
		}
		else
		{
			vec1[k] = rightArray[j];
			++k; ++j;
		}        
	}

	// one of the arrays might be long hence run left over.

	while(i<leftArraySize)
	{
		vec1[k]=leftArray[i];
		++k; ++i;
	}

	while(j<rightArraySize)
	{
		vec1[k]=rightArray[j];
		++k; ++j;
	}    
}

int main(int argc, char* argv[])
{
	vector<int> vec1;
	vec1.reserve(8);

	// push 4 elements still 4 capacity left.
	vec1.push_back(1);
	vec1.push_back(3);
	vec1.push_back(5);
	vec1.push_back(7);

	// second sorted vector.
	vector<int> vec2 = { 2, 4, 6, 8 };

	// Implement the merging logic. results are written back into vec1.
	mergeArrays(vec1, vec2);

	// print the result.
	for(int i=0; i<8; ++i)
		cout << vec1[i] << " , ";
	cout << '\n';
	return(0);    
}
