#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

bool isArraySorted(const vector<int>& input)
{
	int upCount = 0;
	int downCount = 0;
	int size = input.size();  

	for(int i=0; i<size-1;++i)
	{
		if(input[i+1]-input[i]>=0)
		{
			if(downCount>0)
				return(false);
			++upCount; 
		}
		else
		{
			if(upCount>0)
				return(false);
			++downCount;      
		}
	}

	bool returnStatus = (upCount==0 && downCount==0) || (upCount==0 && downCount>0) || (downCount==0 && upCount>0);
	return(returnStatus);
}

int getVectorProduct(const vector<int>& input)
{
	int product=1;
	for(const auto& iter : input)
		product*=iter;
	return(product);
}

bool isContiguous(const vector<int>& input)
{
	int size=input.size();
	for(int i=0; i<size-1; ++i)
	{
		if(input[i+1]-input[i]>1)
			return(false);	
	}
	return(true);
}

void printVector(const vector<int>& input)
{
	if(input.size()>0)
	{
		for(int i=0; i<input.size()-1;++i)
			cout << input[i] << " , ";
		cout << input[input.size()-1] << '\n';
	}
}

void printSubsequentArrays(vector<vector<int>>& results, const int& limit)
{
	int size=results.size();
	int count=0;

	// print the results.
	for(int i=0; i<size; ++i)
	{
		vector<int>& ref = results[i];
		bool sortStatus = isArraySorted(ref);
		bool contiguous = isContiguous(ref);
		int product = getVectorProduct(ref);
		if(product<limit && contiguous)
		{
			printVector(ref);
			++count;
		}
	}
	 cout << "total solutions = " << count << '\n';
}

void printPossibleSets(const vector<int>& input, vector<vector<int>>& results)
{
	int size = input.size();
	vector<int> holder;
	holder.reserve(size);

	for(int i=0; i<(1<<size); ++i)
	{
		for(int j=0; j<size; ++j)
		{
			if(i&(1<<j))
			{        
				holder.push_back(input[j]);
			}
		}
		results.push_back(holder);
		holder.clear();
	}
}

int main(int argc, char* argv[])
{
	// input list.
	vector<int> vec = { 1, 2, 3, 4 };  

	// sort the array.
	sort(vec.begin(), vec.end(), less<int>());

	// reserve the size for output.
	vector<vector<int>> results;
	results.reserve(1<<vec.size());
	for(unsigned int i=0; i<results.size(); ++i)
		results[i].reserve(vec.size());  

	// core logic.
	printPossibleSets(vec, results);
	printSubsequentArrays(results, 10);		
	return(0);  
}
